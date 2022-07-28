//
// Created by Jacky on 2021/12/7.
//

#ifndef LOGLEVEL_H
#define LOGLEVEL_H

#pragma once

// 定义LogLevel
// 使用uint8，自带无锁操作
enum class LogLevel : uint8_t {
    INFO = 0,
    DEBUG = 1,
    WARN = 2,
    ERROR = 3,
    FATAL = 4
};


#endif // LOGLEVEL_H
