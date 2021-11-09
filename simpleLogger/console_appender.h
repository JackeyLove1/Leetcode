//
// Created by Jacky on 2021/11/8.
//

#ifndef STUDY_CONSOLE_APPENDER_H
#define STUDY_CONSOLE_APPENDER_H
#include "appender.h"

class ConsoleAppender: public Appender{
public:
    virtual ~ConsoleAppender(){}
    virtual void append(const std::string& line);
};

#endif //STUDY_CONSOLE_APPENDER_H
