//
// Created by Jacky on 2021/12/7.
//

#ifndef LOGGER_H
#define LOGGER_H

#pragma once

#include <utility>
#include <vector>
#include <list>
#include <mutex>
#include <memory>
#include <thread>
#include <atomic>
#include <chrono>
#include <cassert>

#include "util.h"
#include "LogLevel.h"
#include "LogBuffer.h"
#include "LogFile.h"

// 日志类
// 定义宏
#define LOG_INFO(msg) Logger::write2("INFO", msg);
#define LOG_ERROR(msg) Logger::write2("ERROR", msg);
#define LOG_WARN(msg) Logger::write2("WARN", msg);
#define LOG_DEBUG(msg) Logger::write2("DEBUG", msg);

class Logger : NoCopyable {
public:
    static Logger *getLogger() {
        return Singleton<Logger>::getInstance();
    }

    // 写日志，对外给宏函数使用
    template<typename ... Args>
    void writelog(LogLevel log_level, const char *format, Args...);

    // 设置日志级别
    void setLogLevel(LogLevel level_);

    // 初始化日志参数
    void initLogger();

    // 关闭日志
    void shutDown();

    // 简单写函数
    void write2(const std::string &type, const std::string &msg);

    // 强制刷盘
    void flush();

    // 获得写入的数据量
    uint64_t getMemoryUsage() {return memory_usage_.load();}

    // 专门为测试读写速度准备的接口
    void writetest(const std::string& msg);

private:
    // 初始化
    void initLogBuffer();

    // 当buffer不够的时候创建新的buffer
    // void createNewLogBuffer();

    // write log 实际调用的函数
    void write(const std::string &msg);

private:
    const int DEBUG = 1;
    constexpr static size_t DefaultBufferSize = 5;

private:
    // 初始化缓冲区大小
    size_t init_used_size_ = DefaultBufferSize;

    // 写日志链表，生产者，用于写日志
    std::vector<std::shared_ptr<LogBuffer>> free_buffer_;
    std::mutex free_buffer_mutex_;

    // 当前正在写入buffer
    // 写buffer时需要上 buffer_mutex_
    std::shared_ptr<LogBuffer> curr_buffer_;
    std::mutex buffer_mutex_;

    // 异步刷新链表，消费者，用于后台刷盘
    std::vector<std::shared_ptr<LogBuffer>> persist_buffer_;
    std::mutex persist_buffer_mutex_;
    // 刷盘时间，单位秒
    size_t persist_period_;

    // 落盘文件
    std::unique_ptr<LogFile> log_file_;

    std::atomic<uint64_t> memory_usage_;

    std::string directory_path_;

    std::mutex logger_mutex_;

    std::condition_variable cond_;

    std::atomic<bool> ready_;
    std::atomic<bool> stop_; // 关机标志

    // std::unique_ptr<std::thread> async_write_thread_;
    std::unique_ptr<std::thread> async_persist_thread_;

    // 通过setLogLevel设置
    LogLevel log_level_;
};

void Logger::initLogger() {

    // 初始化buffer
    initLogBuffer();
    curr_buffer_ = std::move(free_buffer_.back());
    free_buffer_.pop_back();

    // 设置默认日志级别, 默认最低日志级别
    log_level_ = LogLevel::INFO;

    // 初始化标志变量
    ready_ = false;
    stop_ = false;
    memory_usage_ = 0;

    // 默认1s刷盘一次
    persist_period_ = 1;

    // 初始化log_file_
    log_file_ = std::make_unique<LogFile>();

    // 创建异步线程
    std::function<void()> thread_persist_ = [this]() {
        while (true) {
            {   // 创建log_locker 的匿名变量区间
                std::unique_lock log_locker(logger_mutex_);
                // 等待一定时间唤醒刷盘或者被ready唤醒
                cond_.wait_for(log_locker, std::chrono::seconds(persist_period_),
                               [&]() { return ready_.load() || stop_.load(); });

                if (stop_.load()) {
                    if (DEBUG) std::cout << "persist thread exit ... " << std::endl;
                    return; // 检测是否中止
                }

                {
                    std::unique_lock persist_locker(persist_buffer_mutex_);
                    // 对persist_buffer_进行dump
                    for (auto &buffer : persist_buffer_) {
                        // 写入log_file_
                        log_file_->writeFile(buffer->getData());
                        // 已经写入后，重置buffer
                        buffer->clear();
                    }
                    ready_.store(false);

                }

                {   // 创建匿名变量区，以自动解锁locker
                    // 使用scoped_lock同时锁定两把锁
                    // (然后交换缓冲区)展示不使用交换缓冲区的方法
                    std::scoped_lock locker(persist_buffer_mutex_, free_buffer_mutex_);
                    // std::swap(persist_buffer_, free_buffer_);
                    while (!persist_buffer_.empty()) {
                        free_buffer_.push_back(std::move(persist_buffer_.back()));
                        persist_buffer_.pop_back();
                    }
                }

            }
        }
    };

    async_persist_thread_ = std::make_unique<std::thread>(std::move(thread_persist_));
    // 启动然后分离异步刷新线程，后台自动刷新
    async_persist_thread_->detach();
}

void Logger::shutDown() {
    // 重置stop
    stop_.store(true);
    // 唤醒所有线程
    cond_.notify_all();
}

void Logger::write(const std::string &msg) {
    // 对buffer进行写操作
    // 上buffer_mutex_锁
    // 先判断目前的buffer是否能够写得下,写得下直接写入
    // 若写不下，再同时上free_buffer_mutex_ && persist_buffer_mutex_
    // 将写满的buffer放入persist_buffer_
    // 从free_buffer_取一个新的buffer写
    // 若free_buffer_为空，那么创建一个新的buffer
    std::unique_lock buffer_locker(buffer_mutex_);
    assert(curr_buffer_ != nullptr);
    if (curr_buffer_->writeBuffer(msg)) {
        // 返回true，代表成功写入
        memory_usage_ += static_cast<uint64_t>(msg.size());
        return;
    }
    std::scoped_lock merge_locker(free_buffer_mutex_, persist_buffer_mutex_);
    assert(curr_buffer_ != nullptr);
    persist_buffer_.push_back(std::move(curr_buffer_));
    // persist_buffer_不为空了，可以唤醒刷新了
    ready_.store(true);
    cond_.notify_one();
    if (free_buffer_.empty()) {
        curr_buffer_ = std::make_shared<LogBuffer>();
    }
    else{
        curr_buffer_ = std::move(free_buffer_.back());
        free_buffer_.pop_back();
    }
    memory_usage_ += static_cast<uint64_t>(msg.size());
    curr_buffer_->writeBuffer(msg);
}

template<typename ... Args>
void Logger::writelog(LogLevel log_level, const char *format, Args... args) {
    // 检查日志级别，低级别日志不输出
    if (log_level < log_level_) {
        return;
    }

    std::string log_line_;
    log_line_.reserve(100);
    log_line_.append(get_time_str());
    log_line_.append(get_pid());
    log_line_.append(__FILE__);
    log_line_.append(std::to_string(__LINE__));
    log_line_.append(__FUNCTION__);
    log_line_.append(argcat(std::forward<Args>(args)...));
    log_line_.append("\n");

    write(log_line_);

}

void Logger::initLogBuffer() {

    // 预先申请足够的空间，节约时间
    free_buffer_.reserve(init_used_size_);
    persist_buffer_.reserve(init_used_size_);

    // 加入一些预写的缓冲区
    for (int i = 0; i < init_used_size_; ++i) {
        free_buffer_.emplace_back(std::make_unique<LogBuffer>());
    }
}

void Logger::setLogLevel(LogLevel level_) {
    log_level_ = level_;
}

inline void Logger::write2(const std::string &type, const std::string &msg) {
    std::string log_line_ = "[" + type + get_time_str() + get_pid() + __FILE__
                            + std::to_string(__LINE__) + "-->" + __FUNCTION__ + " ] " + msg + "\n";
    write(log_line_);
}

void Logger::flush() {
    // 取得curr_buffer_mutex_， persist_buffer_mutex_ 和free_buffer_mutex
    // 将旧curr_buffer_加入persist_buffer_
    // 将curr_buffer 换成新的buffer(从free_buffer_ 或者重新申请)
    // 解锁三把锁，唤醒cond_和异步刷新线程
    std::scoped_lock(buffer_mutex_, persist_buffer_mutex_, free_buffer_mutex_);
    persist_buffer_.push_back(std::move(curr_buffer_));
    if (free_buffer_.empty()) {
        curr_buffer_ = std::move(free_buffer_.back());
        free_buffer_.pop_back();
        return;
    }
    curr_buffer_ = std::make_shared<LogBuffer>();
    ready_.store(true);
    cond_.notify_all();

}


void Logger::writetest(const std::string &msg) {
    write(msg);
}

#endif // LOGGER_H
