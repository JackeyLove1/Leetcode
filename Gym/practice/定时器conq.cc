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

using namespace std;
using namespace std::chrono_literals;

template<typename T>
class threadsafe_queue {
private:
    threadsafe_queue(const threadsafe_queue &) = delete;

    threadsafe_queue &operator=(const threadsafe_queue &) = delete;

private:
    mutable std::mutex mutex_;
    std::condition_variable cond_;
    std::queue<T> data_;

public:
    threadsafe_queue() = default;

    void push(T value) {
        std::lock_guard lk(mutex_);
        data_.push(value);
        cond_.notify_all();
    };

    bool try_pop(T &value) {
        std::unique_lock lk(mutex_);
        if (data_.empty()) {
            return false;
        }
        value = data_.front();
        data_.pop();
        return true;
    };

    std::shared_ptr<T> try_pop() {
        // TODO
        return nullptr;
    };

    void wait_and_pop(T &value) {
        std::unique_lock lk(mutex_);
        // cond_.wait(lk, [this] { return !data_.empty(); });
        // cond_.wait(lk);
        cond_.wait_for(lk, 10ms);
        if (data_.empty()) {
            return;
        }
        value = data_.front();
        data_.pop();
    };

    std::shared_ptr<T> wait_and_pop() {
        //TODO
        return nullptr;
    };

    bool empty() const {
        std::lock_guard lk(mutex_);
        return data_.empty();
    }
};

static threadsafe_queue<int> tq;
static constexpr int N = 100;
static constexpr int TIME_SLEEP = 10;
static atomic<bool> stop_ = false;

void producter(int id) {
    for (int i = 0; i < N; ++i) {
        tq.push(i);
        printf("%d push %d\n", id, i);
        std::this_thread::sleep_for(std::chrono::milliseconds(TIME_SLEEP));
    }
    printf("producer %d is done\n", id);
}

void comsumer(int id) {
    for (int i = 0; i < N; ++i) {
        int t;
        tq.wait_and_pop(t);
        printf("%d get %d\n", id, t);
        // std::this_thread::sleep_for(std::chrono::milliseconds(TIME_SLEEP));
    }
    printf("consumer %d is done\n", id);
}

void producter2(int id) {
    for (int i = 0; i < N; ++i) {
        tq.push(i);
        printf("%d push %d\n", id, i);
        // std::this_thread::sleep_for(std::chrono::milliseconds(TIME_SLEEP));
    }
    printf("producer %d is done\n", id);
}

void comsumer2(int id) {
    while (!stop_) {
        int t;
        tq.wait_and_pop(t);
        printf("%d get %d\n", id, t);
        // std::this_thread::sleep_for(std::chrono::milliseconds(TIME_SLEEP));
    }
    printf("consumer %d is done\n", id);
}

void Test2() {
    thread t1(producter2, 1);
    thread t2(comsumer2, 1);
    thread t3(comsumer2, 2);
    thread t4(producter2, 2);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}

int main() {
    thread click([&]() {
        printf("click is running...\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(TIME_SLEEP * 100));
        printf("Send the stop signal ...\n");
        stop_ = true;
    });
    click.detach();
    Test2();
    return 0;
}

