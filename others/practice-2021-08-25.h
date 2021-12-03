//
// Created by Jacky on 2021/8/25.
//

#ifndef PRACTICE_2021_08_25_H
#define PRACTICE_2021_08_25_H

#include <cstring>
#include <iostream>

class String {
public:
    String(const char *cstr = 0);

    String(const String &str);

    String &operator=(const String &str);

    ~String();

    char *get_cstr() const { return m_data; }

    friend std::ostream &operator<<(std::ostream &os, const String &);

private:
    char *m_data;
};

String::String(const char *cstr) {
    if (cstr) {
        size_t len = strlen(cstr) + 1;
        m_data = new char[len];
        strcpy(m_data, cstr);
    } else {
        m_data = new char[1];
        m_data[0] = '\0';
    }
}

String::String(const String &str) {
    m_data = new char[strlen(str.get_cstr()) + 1];
    strcpy(m_data, str.get_cstr());
}

String &String::operator=(const String &str) {
    if (this == &str) {
        return *this;
    }
    delete[]m_data;
    m_data = new char[strlen(str.get_cstr()) + 1];
    strcpy(m_data, str.get_cstr());
    return *this;
}

String::~String() {
    delete[]m_data;
}

std::ostream &operator<<(std::ostream &os, const String &str) {
    os << "String is: " << str.get_cstr();
    return os;
}


class String2 {
private:
    struct StringValue {
        int refCount;
        char *m_data;

        explicit StringValue(const char *cstr = "");

        ~StringValue();
    };

    StringValue *value;

public:
    String2(const char *cstr = "");

    String2(const String2 &);

    String2 &operator=(const String2 &);

    ~String2();

    const char &getIndex(size_t index);

    char *get_cstr() const { return value->m_data; }
};

const char &String2::getIndex(size_t index) {
    return value->m_data[index];
}

String2::String2(const char *cstr) : value(new StringValue(cstr)) {

}

String2::String2(const String2 &rhs) : value(rhs.value) {
    ++value->refCount;
}

String2 &String2::operator=(const String2 &rhs) {
    if (this == &rhs) {
        return *this;
    }
    // 解绑原有值
    if (--value->refCount == 0) delete value;
    value = rhs.value;
    ++value->refCount;
    return *this;
}

String2::~String2() {
    if (--value->refCount == 0) {
        delete value;
    }
}

String2::StringValue::StringValue(const char *cstr) : refCount(1) {
    if (cstr) {
        m_data = new char[strlen(cstr) + 1];
        strcpy(m_data, cstr);
    } else {
        m_data = new char[1];
        m_data[0] = '\0';
    }
}

String2::StringValue::~StringValue() {
    delete[] m_data;
}

template<typename T>
class SmartPtr;

template<typename T>
class RefPtr {
private:
    friend class SmartPtr<T>;

    RefPtr(T *ptr) : p(ptr), count(1) {};

    ~RefPtr() { delete p; }

    int count;
    T *p;
};

template<typename T>
class SmartPtr {
public:
    SmartPtr(T *ptr) : rp(new RefPtr<T>(ptr)) {};

    SmartPtr(const SmartPtr<T> &sp) : rp(sp.rp) { ++rp->count; }

    SmartPtr &operator=(const SmartPtr<T> &rhs) {
        ++rhs.rp.count;
        if (--rp->count == 0) {
            delete rp;
        }
        rp = rhs.rp;
        return *this;
    }

    T &operator*() {
        return *(rp->p);
    }

    T *operator&() {
        return rp->p;
    }

    ~SmartPtr() {
        if (--rp->count == 0) {
            delete rp;
        }
    }

private:
    RefPtr<T> *rp;
};

class Singleton {
private:
    static Singleton *instance;

    Singleton() {}

    ~Singleton();

public:
    static Singleton *get_instance() {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
};

class no_copy{
public:
    no_copy(){};
    no_copy(const no_copy&) = delete ;
    no_copy& operator = (const no_copy&) = delete ;
};

#endif
