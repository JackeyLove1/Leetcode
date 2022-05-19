//
// Created by Jacky on 2022/5/18.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include <chrono>
#include <atomic>

using namespace std;
using namespace std::chrono_literals;

std::mutex mu_;
std::condition_variable cond_;
std::string flag("A");
std::atomic<bool> stop_ = false;
std::atomic<int> count_ = 1;
static constexpr int N = 5;

void funcA() {
    while (!stop_ && count_ < N) {
        std::unique_lock lk(mu_);
        while (flag == "B") {
            cond_.wait(lk);
            this_thread::sleep_for(100ms);
        }
        std::cout << flag << endl;
        flag = "B";
        count_ += 1;
        cond_.notify_all();
    }
}

void funcB() {
    while (!stop_ && count_ <= N) {
        std::unique_lock lk(mu_);
        while (flag == "A") {
            cond_.wait(lk);
            this_thread::sleep_for(100ms);
        }
        std::cout << flag << endl;
        flag = "A";
        count_ += 1;
        cond_.notify_all();
    }
}

int main() {
    thread A(funcA);
    thread B(funcB);
    thread C([&]() {
        this_thread::sleep_for(1s);
        stop_ = true;
    });
    A.join();
    B.join();
    C.join();
    return 0;
}