//
// Created by Jacky on 2021/11/8.
//

#ifndef STUDY_APPENDER_H
#define STUDY_APPENDER_H

#include <string>

class Appender {
public:
    virtual ~Appender() {}

    virtual void append(const std::string &line) = 0;
};


#endif //STUDY_APPENDER_H
