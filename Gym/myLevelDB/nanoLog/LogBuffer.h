//
// Created by Jacky on 2021/12/7.
//

#ifndef LOGBUFFER_H
#define LOGBUFFER_H

#pragma once

// LogBuffer
class LogBuffer;

class LogBuffer : NoCopyable {
private:
    constexpr static size_t LogBufferDefaultSize = 4 * 1024 * 1024; // 4M
public:
    enum class status : uint8_t {
        FULL = 1,
        FREE = 0
    };

    // 初始化函数
    // 设置参数, 给data_预留出足够的空间
    explicit LogBuffer()
            : curr_left_(LogBufferDefaultSize), curr_status_(status::FREE), curr_used_(0) {
        data_.reserve(LogBufferDefaultSize);
    }

    // 向LogBuffer写入日志
    bool writeBuffer(const std::string &str);

    // 清空复用
    void clear();

    // 获取日志
    std::string getData() { return data_; }

    // 获取状态
    [[nodiscard]] status getStatus() const { return curr_status_; }

    // 获取使用空间大小
    [[nodiscard]] size_t getMemoryUsage() const { return curr_used_; }

    // 获取剩余空间大小
    [[nodiscard]] size_t getMemorySpace() const { return curr_left_; }

private:
    // 当前的状态，写满或者未写满
    status curr_status_;

    // 保存的日志
    std::string data_;

    // 剩余空间
    size_t curr_left_;

    // 已经日志大小
    size_t curr_used_;
};

bool LogBuffer::writeBuffer(const std::string &str) {
    // 如果剩余空间够的话直接写入, return true
    // 不够的话，设置状态为FULL，return false
    // Logger根据返回的状态判断是否要使用新的LogBuffer
    if (str.size() < curr_left_) {
        data_.append(str);
        curr_used_ += str.size();
        curr_left_ -= str.size();
        return true;
    }
    curr_status_ = status::FULL;
    return false;
}

void LogBuffer::clear() {
    curr_status_ = status::FREE;
    data_.clear(); // C++的实现保证不会回收空间
    curr_left_ = LogBufferDefaultSize;
    curr_used_ = 0;
}

#endif // LOGBUFFER_H

// test file
/*
int main() {
    LogBuffer log_buffer_;
    const string s = "hello, world!";
    auto start = chrono::steady_clock::now();
    const int N = 100000;
    for (int i = 0; i < N; ++i) {
        log_buffer_.writeBuffer(s);
    }
    auto end = chrono::steady_clock::now();

    auto time_diff = end - start;
    auto duration = chrono::duration_cast<chrono::milliseconds>(time_diff);
    cout << "Operation cost : " << duration.count() << "ms" << endl;
    cout << "memory used: " << log_buffer_.getMemoryUsage() << endl;
    log_buffer_.clear();
    cout << "memory left: " << log_buffer_.getMemorySpace() << endl;
}
 */