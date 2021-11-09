//
// Created by Jacky on 2021/11/8.
//

#ifndef STUDY_LOGGER_H
#define STUDY_LOGGER_H

#include <string>
#include <vector>
#include <cstdarg>
#include <memory.h>

#include "appender.h"

class Logger {
public:
    Logger() {}

    ~Logger();

    void log(const std::string &level, const std::string &str);

    void log(const char *level, const char *format, ...);

    void addAppender(Appender *);

private:
    std::string getTime();

    void writeLog(const std::string &, const std::string &str);

    std::string format(const std::string &, const std::string &);

private:
    static const int MAX_LINE = 4096;

    char mLogStr[MAX_LINE];

    std::vector<Appender*>mAppenderList;

};

#endif //STUDY_LOGGER_H
