//
// Created by Jacky on 2022/5/15.
//

#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <iostream>
#include <condition_variable>
#include <thread>
#include <memory>
#include <ctime>
#include <chrono>
#include <cstdio>
#include <string>
#include <queue>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cassert>

static constexpr size_t BUFFER_SIZE = 1024 * 1024 * 10;
static constexpr size_t BUFFER_NUM = 16;
static constexpr int FLUSH_INTERVAl = 100;
static constexpr int WRITE_NUM = 1000000;
using namespace std::chrono_literals;

// thread wrapper
class Thread {
private:
    Thread(const Thread &) = delete;

    Thread &operator=(const Thread &) = delete;

private:
    using Func = std::function<void(void)>;
    Func func_;
    std::atomic<bool> start_;
    std::thread t_;
public:
    explicit Thread(Func func) : func_(std::move(func)), start_(false) {}

    ~Thread() {
        if (start_ && t_.joinable()) {
            t_.detach();
        }
    }

    void start() {
        printf("Thread Start ... \n");
        t_ = std::move(std::thread(func_));
        start_ = true;
    }

    void join() {
        if (t_.joinable()) {
            t_.join();
        }
    }

};

class LogBuffer {
public:
    LogBuffer() {
        data_ = new char[total];
    }

    ~LogBuffer() {
        delete[] data_;
    }

    size_t available() const {
        return available_;
    }

    size_t length() const {
        return total - available_;
    }

    const char *data() const {
        return data_;
    }

    void clear() {
        cur_ = 0;
        available_ = total;
    }

    void append(const char *msg, size_t len) {
        memcpy(data_ + cur_, msg, len);
        cur_ += len;
        available_ -= len;
    }

private:
    char *data_;
    const size_t total = BUFFER_SIZE;
    size_t cur_;
    size_t available_;
};


class AsyncFileWriter {
private:
    AsyncFileWriter &operator=(const AsyncFileWriter &) = delete;

    AsyncFileWriter(const AsyncFileWriter &) = delete;

public:

    explicit AsyncFileWriter();

    ~AsyncFileWriter();

    void append(const char *msg, size_t len);

    void start();

    void stop();

private:
    void threadFunc();

    std::atomic<bool> start_;
    std::atomic<bool> running_;

    mutable std::mutex mutex_;
    std::condition_variable cond_;
    Thread persist_thread_;
    std::unique_ptr<LogBuffer> cur_buffer_;
    std::unique_ptr<LogBuffer> next_buffer_;
    std::vector<std::unique_ptr<LogBuffer>> buffer_;
};

AsyncFileWriter::AsyncFileWriter()
        : start_(false), running_(false),
          persist_thread_(std::bind(&AsyncFileWriter::threadFunc, this)),
          cur_buffer_(std::make_unique<LogBuffer>()),
          next_buffer_(std::make_unique<LogBuffer>()) {
    // start();
    buffer_.reserve(BUFFER_NUM);
    cur_buffer_->clear();
    next_buffer_->clear();
}

AsyncFileWriter::~AsyncFileWriter() {
    if (start_) {
        stop();
    }
}

void AsyncFileWriter::threadFunc() {
    // printf("Hello, World\n");
    assert(running_ == true);
    std::unique_ptr<LogBuffer> newBuffer1(new LogBuffer);
    std::unique_ptr<LogBuffer> newBuffer2(new LogBuffer);
    std::vector<std::unique_ptr<LogBuffer>> buffer2Write;
    buffer2Write.reserve(16);
    while (running_) {
        {
            std::unique_lock lk(mutex_);
            if (buffer_.empty()) {
                cond_.wait_for(lk, FLUSH_INTERVAl * 1ms);
            }
            buffer_.push_back(std::move(cur_buffer_));
            cur_buffer_ = std::move(newBuffer1);
            if (next_buffer_ != nullptr) {
                next_buffer_ = std::move(newBuffer2);
            }
            buffer_.swap(buffer2Write);
        }
        // lk is deconstructing

        if (!buffer2Write.empty()) {
            if (buffer2Write.size() > 16) {
                // drop some buffers
                buffer2Write.erase(buffer2Write.begin() + 2, buffer2Write.end());
            }
            for (const auto &buffer : buffer2Write) {
                // using output instead of flush
                std::string output(buffer->data(), buffer->length());
                buffer->clear();
                // std::cout << output << std::endl;
            }
        }

        if (buffer2Write.size() > 2) {
            buffer2Write.resize(2);
        }

        if (newBuffer1 != nullptr) {
            newBuffer1 = std::move(buffer2Write.back());
            buffer2Write.pop_back();
            newBuffer1->clear();
        }

        if (newBuffer2 != nullptr) {
            newBuffer2 = std::move(buffer2Write.back());
            buffer2Write.pop_back();
            newBuffer2->clear();
        }
    }

}

void AsyncFileWriter::start() {
    start_ = true;
    running_ = true;
    persist_thread_.start();
}

void AsyncFileWriter::stop() {
    start_ = false;
    running_ = false;
    cond_.notify_one();
    persist_thread_.join();
}

void AsyncFileWriter::append(const char *msg, size_t len) {
    std::lock_guard lk(mutex_);
    if (cur_buffer_->available() > len) {
        cur_buffer_->append(msg, len);
    } else {
        buffer_.push_back(std::move(cur_buffer_));
        if (next_buffer_) {
            cur_buffer_ = std::move(next_buffer_);
        } else {
            cur_buffer_.reset(new LogBuffer);
        }
        cur_buffer_->append(msg, len);
        cond_.notify_one(); // wake the flush thread(threadFunc)
    }
}

int main() {
    AsyncFileWriter asyncFileWriter;
    const std::string msg = "Hello, World!";
    size_t len = strlen(msg.c_str());
    std::cout << "len: " << len << std::endl;
    asyncFileWriter.start();
    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < WRITE_NUM; ++i) {
        asyncFileWriter.append(msg.c_str(), len);
    }
    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Cost: " << duration.count() << " ms" << std::endl;
    asyncFileWriter.stop();
    return 0;
}