//
// Created by Jacky on 2022/5/7.
//
#include <chrono>
#include <ctime>
#include <string>

const std::string getCurrentSystemTime() {
    auto tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm *ptm = localtime(&tt);
    char date[60] = {0};
    sprintf(date, "%d-%02d-%02d  %02d:%02d:%02d",
            (int) ptm->tm_year + 1900, (int) ptm->tm_mon + 1, (int) ptm->tm_mday,
            (int) ptm->tm_hour, (int) ptm->tm_min, (int) ptm->tm_sec);
    return std::string(date);
}