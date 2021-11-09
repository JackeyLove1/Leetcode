//
// Created by Jacky on 2021/11/8.
//

#include "file_appender.h"

void FileAppender::append(const std::string &line) {
    if(mLogFile.is_open()){
        mLogFile.write(line.c_str(), line.length());
        mLogFile.flush();
    }
}

// 我们为这个类增加一个tie()方法，用来绑定日志文件的文件名
void FileAppender::tie(const std::string &fileName) {
    if(mLogFile.is_open()){
        mLogFile.close();
    }
    mLogFile.open(fileName.c_str(), std::ios::app | std::ios::out);
}