//
// Created by Jacky on 2021/12/7.
//

#ifndef LOGFILE_H
#define LOGFILE_H

#pragma once

#include <filesystem>
#include <sstream>
#include <fstream>
#include <ostream>
#include <string>
#include <cstring>

#include "util.h"

// 使用C++17特性实现文件写入操作
// 写入LogBuffer的data_
// 若空间不够，则打开一个新文件继续写入

namespace fs = std::filesystem;

class LogFile : NoCopyable {
private:
    constexpr static int DEBUG = 0;
    constexpr static size_t LogFileDefaultSize = 64 * 1024 * 1024; // 64M
    constexpr static uint64_t MOD = 1000000;
    const std::ios_base::openmode MODE = std::ios::app | std::ios::out | std::ios::in | std::ios::binary;
public:
    LogFile(std::string directory_ = "");

    ~LogFile();

public:
    // 写入LogBuffer的data_
    void writeFile(const std::string &buffer_data_);

    // 获取当前文件名
    std::string getFileName() const { return curr_file_name_; };

    // 获取本文件已经写入的大小
    size_t getFileSize() const { return file_used_; }

    // 获取本文件的剩余空间
    size_t getFileFree() const { return file_free_; }

private:
    // 创建新文件
    void createNewFile();

    // 重置参数
    void clear();

private:
    // 写入的文件
    std::ofstream file_;

    // 当前的文件名
    std::string curr_file_name_;

    // 当前文件所在的路径
    std::string curr_file_path_;

    // 文件已经使用的空间
    size_t file_used_;

    // 文件剩余空间
    size_t file_free_;

    // 文件计数
    size_t log_file_count_;

};

LogFile::LogFile(std::string directory_)
        : file_used_(0), file_free_(LogFileDefaultSize), log_file_count_(0) //
{
    if (directory_.empty() || !fs::exists(directory_)) {
        // 如果没有指定文件夹或者没找到位置
        // 就在当前文件下生成一个文件夹
        // 增加一个前缀时间戳去重
        auto curr_path_ = fs::current_path() / "log" / std::to_string(get_timestamp() / MOD);
        directory_ = curr_path_.string();
    }

    if (fs::exists(directory_)) {
        // 发现有重名文件夹就抛出异常
        throw std::runtime_error("Found a folder with the same name！");
    }

    fs::create_directories(directory_);
    curr_file_path_ = directory_;

    // 使用文件夹名称 + 当前日期 + 文件计数数目生成日志
    auto curr_file_name_path_ = fs::path(curr_file_path_) / (get_date() + std::to_string(log_file_count_) + ".log");
    curr_file_name_ = curr_file_name_path_.string();
    // std::cout << "curr_file_path_ " << curr_file_path_ << std::endl;
    // std::cout << "curr_file_name_ " << curr_file_name_ << std::endl;
}

LogFile::~LogFile() {
    if (file_.is_open()) {
        file_.flush();
        file_.close();
    }
}

// 重置参数，仅用于createNewFile中
void LogFile::clear() {
    if (file_.is_open()) {
        file_.flush();
        file_.close();
    }
    file_used_ = 0;
    file_free_ = LogFileDefaultSize;
    log_file_count_++; // 标记增加，生成新的curr_file_name_
    auto curr_file_name_path_ = fs::path(curr_file_path_) / get_date() / std::to_string(log_file_count_);
    curr_file_name_ = curr_file_name_path_.string();
    // std::ofstream ostrm(curr_file_name_path_, MODE);
    // file_.swap(ostrm);
}

// 当前文件写满时，创建一个新的文件
void LogFile::createNewFile() {
    clear();
}

void LogFile::writeFile(const std::string &buffer_data_) {
    if (buffer_data_.size() >= file_free_) {
        // 空间不够，需要创建新文件
        createNewFile();
    }
    // 空间足够，可以安全写入
    // 检查file是否打开，没打开通过curr_file_name_ 打开
    // 打开时使用追加模式，可读可写，暂时不使用二进制
    if (!file_.is_open()) {
        file_.open(curr_file_name_, MODE);
    }
    // 写入文件
    file_ << buffer_data_;
    if (DEBUG) std::cout << "write: " << buffer_data_ << std::endl;
}


#endif //MYLEVELDB_LOGFILE_H

// 测试文件如下
/*
int main() {
    LogFile log_file_;
    const string s = "hello, world!";
    constexpr int N = 100000;
    auto start = chrono::steady_clock::now();
    for (int i = 0; i < N; ++i) {
        log_file_.writeFile(s);
    }
    auto end = chrono::steady_clock::now();
    auto time_diff = end - start;
    auto duration = chrono::duration_cast<chrono::milliseconds>(time_diff);
    cout << "Operation cost : " << duration.count() << "ms" << endl;
}
 */