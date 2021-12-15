//
// Created by Jacky on 2021/12/7.
//

#ifndef UTIL_H
#define UTIL_H

#pragma once

#include <sstream>
#include <chrono>
#include <ctime>
#include <mutex>
#include <string>
#include <ostream>

// util

// 获取当前线程ID
inline std::string get_pid() {
    std::stringstream ss;
    ss << std::this_thread::get_id();
    return ss.str();
}

// 获取当前时间
inline std::string get_time_str() {
    time_t time_now;
    time(&time_now);
    char time_cstr[64];
    strftime(time_cstr, sizeof(time_cstr), "%Y-%m-%d %H:%M:%S", localtime(&time_now));
    return time_cstr;
}

// 获得当前日期
inline std::string get_date(){
    auto time_str = get_time_str();
    auto space_pos = time_str.find_first_of(' ');
    return time_str.substr(0, space_pos);
}

// 获取当前时间戳
inline uint64_t get_timestamp() {
    // 精确到微妙
    auto d = std::chrono::system_clock::now().time_since_epoch();
    auto mic = duration_cast<std::chrono::microseconds>(d);
    return static_cast<uint64_t>(mic.count());
}

// 单例模式
static std::once_flag once_control;

template<typename T>
class Singleton {
public:
    static T *getInstance() {
        std::call_once(once_control, Singleton::init);
        return value_;
    }

private:
    Singleton() = delete;

    ~Singleton() = delete;

    static void init() {
        value_ = new T();
    }

    static T *value_;
};

template<typename T> T *Singleton<T>::value_ = nullptr;


// 不可拷贝基类
class NoCopyable {
public:
    NoCopyable() = default;

    ~NoCopyable() = default;

protected:
    NoCopyable(const NoCopyable &) = delete;

    NoCopyable &operator=(const NoCopyable &) = delete;
};


// 递归模版组装字符串
template<typename OS,typename T> void ostr(OS& o,T t)
{
    o << t;
}
template<typename... Arg> auto argcat(Arg... arg)->std::string
{
    std::ostringstream os;
    int arr[] = { (ostr(os,arg),0)...};
    return os.str();
}

#endif // UTIL_H
