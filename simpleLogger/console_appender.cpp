//
// Created by Jacky on 2021/11/8.
//

#include "console_appender.h"
#include <iostream>

void ConsoleAppender::append(const std::string &line) {
    std::cout << line << std::endl;
}