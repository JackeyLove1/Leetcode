//
// Created by Jacky on 2022/5/6.
//

// C++ 11单例模式的一个实现
// std::once_flag & std::call_once 实现构造函数的一次调用
// std::atexit 实现程序结束后单例的自动注销

#ifndef TINYLOG_SINGLETON_H
#define TINYLOG_SINGLETON_H
#pragma once

#include <mutex>


template<typename T>
class Singleton {
public:
    // 获取单例
    // 销毁单例
    static void destory() {
        if (value_ != nullptr) {
            delete value_;
        }
    }

    static T *getInstance() {
        // 初始化控制
        static std::once_flag init_flag;
        std::call_once(init_flag, init);
        return value_;
    }

private:
    // 注销四个函数
    Singleton() = delete;

    ~Singleton() = delete;

    Singleton(const Singleton<T> &other) = delete;

    Singleton<T> &operator=(const Singleton<T> &other) = delete;

    // 初始化单例
    static void init() {
        value_ = new T();
        std::atexit(destory);
    }

private:
    // 单例对象
    static T *value_;
};

// 单例对象
template<typename T>
T *Singleton<T>::value_ = nullptr;

#endif //TINYLOG_SINGLETON_H
