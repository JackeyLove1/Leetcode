//
// Created by Jacky on 2022/6/5
//

#include <limits>
#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <type_traits>

using std::cout;
using std::endl;

struct X {
    X() {
        cout << "Create an instance" << endl;
        cout << "p: " << this << endl;
    }

    X(const X &) {
        cout << "Copy" << std::endl;
    }

    X(X &&) {
        cout << "Move" << endl;
    }

    X &operator=(X &&) {
        cout << "= move" << endl;
        return *this;
    }

    X &operator=(const X &) {
        cout << "= copy" << endl;
        return *this;
    }
};

template<typename T>
void swap(T &a, T &b)
noexcept(noexcept(T(std::move(a))) && noexcept(a.operator=(std::move(b)))) {
    static_assert(noexcept(noexcept(T(std::move(a))) && noexcept(a.operator=(std::move(b)))));
    T tmp(std::move(a));
    cout << "Create tmp" << endl;
    a = std::move(b);
    cout << "move b to a" << endl;
    b = std::move(tmp);
    cout << "move tmp to b" << endl;
}

struct aX {
    char a1;
    int a2;
    double a3;
};

struct aX2 {
    alignas(16) char a1;
    alignas(double) int a2;
    double a3;
};

#define ALIGN_COUT(s) cout << sizeof(s) << endl;

template<typename ...Args>
auto sum(Args... args) {
    return (args + ...);
}

template<typename ...Args>
void print(Args... args) {
    (cout << ... << args) << endl;
}

int main() {
    X a, b;
    swap(a, b);
    cout << "pa: " << (&a) << endl;
    cout << "pb: " << (&b) << endl;
    cout << alignof(int) << endl;
    aX x1;
    aX2 x2;
    ALIGN_COUT(x1);
    ALIGN_COUT(x2);
    cout << sum<int>(1, 2, 3, 4, 5) << endl;
    cout << sum(1, 2, 3, 4, 5, 6) << endl;
    print(1, std::string("hello"), 3.14);
}