//
// Created by Jacky on 2022/5/7.
//

#ifndef TINYLOG_THREAD_H
#define TINYLOG_THREAD_H
// C++11 封装线程类
#pragma once

#include <mutex>
#include <atomic>
#include <thread>
#include <functional>

class Thread {
public:
    using Func = std::function<void(void)>;

    // default construct function
    explicit Thread(Func cb);

    // explicit Thread(Func cb, std::string &name);

    ~Thread();

    bool isStarted();

    void start();

    void join();

    // const std::string &getName() const;

    std::thread::id CurrentThreadTid();

private:
    void run();

private:
    Thread(const Thread &) = delete;

    Thread &operator=(const Thread &) = delete;

private:
    std::atomic<bool> started_;
    // std::atomic<bool> joined_;
    // std::string name_;
    Func cb_;
    std::thread task_;
};

Thread::Thread(Func cb) : started_(false), cb_(std::move(cb)), task_(std::thread()) {

}

Thread::~Thread() {
    if (started_ && task_.joinable()) {
        task_.detach();
    }
}

bool Thread::isStarted() {
    return started_;
}

void Thread::start() {
    if (started_) return;
    std::thread t(std::bind(&Thread::run, this));
    task_ = std::move(t);
    started_ = true;
}

void Thread::join() {
    if (task_.joinable()) {
        task_.join();
    }
}


std::thread::id Thread::CurrentThreadTid() {
    return task_.get_id();
}


void Thread::run() {
    cb_();
}

#endif //TINYLOG_THREAD_H
