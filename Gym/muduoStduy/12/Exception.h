//
// Created by Jacky on 2021/11/11.
//

#ifndef STUDY_EXCEPTION_H
#define STUDY_EXCEPTION_H

#include <exception>
#include <string>

class Exception : public std::exception {
public:
    explicit Exception(const char *what);

    explicit Exception(const std::string &what);

    virtual ~Exception() throw();

    virtual const char *what() const throw();

    const char *stackTrace() const throw();

private:
    void fillStackTrace();

    std::string demangle(const char *symbol);

    std::string message_;
    std::string stack_;
};


#endif //STUDY_EXCEPTION_H
