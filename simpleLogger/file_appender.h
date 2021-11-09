//
// Created by Jacky on 2021/11/8.
//

#ifndef STUDY_FILE_APPENDER_H
#define STUDY_FILE_APPENDER_H

#include "appender.h"
#include <string>
#include <fstream>

class FileAppender : public Appender {
public:
    virtual ~FileAppender() {}

    virtual void append(const std::string &line) override;

    void tie(const std::string &);

private:
    std::fstream mLogFile;
};

#endif //STUDY_FILE_APPENDER_H
