#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <utility>
#include <vector>
#include <array>
#include <functional>
#include <any>
#include <variant>
#include <bitset>
#include <type_traits>
#include <numeric>
#include <numbers>
#include <future>
#include <experimental/coroutine>

#define nprint(x) std::cout << (x) << std::endl;
#define cprint(container) std::for_each((container).begin(), (container).end(), [](const auto& e){nprint(e)});

template<typename T>
constexpr T pi(3.1415926535897932385);

template<typename T,
        typename  = std::enable_if_t<(sizeof(T) > 4)>>
void foo() {
    std::cout << "foo" << std::endl;
}

template<typename T>
using EnableUsingString = std::enable_if_t<std::is_convertible_v<T, std::string>>;

class Person {
private:
    std::string name;
public:
    template<typename T, typename = EnableUsingString<T>>
    explicit Person(T &&t): name(std::forward<T>(t)) {
        std::cout << "Template " << name << std::endl;
    }

    Person(Person const &p) : name(p.name) {
        std::cout << "Copy" << std::endl;
    }

    Person(Person &&p) : name(std::move(p.name)) {
        std::cout << "Move" << std::endl;
    }
};

template<typename T, typename = std::enable_if<std::is_const_v<T>, void>>
void outR(T &arg) {
    // do something
}

constexpr bool IsPrime(unsigned int p) {
    for (unsigned int d = 2; d <= p / 2; ++d) {
        if (p % d == 0) {
            return false;
        }
    }
    return p > 1;
}

template<typename T, typename ... Types>
void print(T const &firstArg, Types const &... args) {
    std::cout << firstArg << std::endl;
    if constexpr(sizeof ... (args) > 0) {
        print(args ...);
    }
}

template<typename Iter, typename Callable, typename... Args>
void foreach(Iter current, Iter end, Callable op, Args const &... args) {
    while (current != end) {
        std::invoke(op, args..., *current);
        ++current;
    }
}

struct Foo {
    Foo(int num) : num_(num) {}

    void print_add(int i) const { std::cout << num_ + i << std::endl; }

    int num_;
};

void print_num(int i) {
    std::cout << i << std::endl;
}

struct PrintSum {
    void operator()(int i) const {
        std::cout << i << std::endl;
    }
};

template<typename Callable, typename... Args>
decltype(auto) call(Callable &&F, Args &&... args) {
    std::invoke(std::forward<Callable>(F), std::forward<Args>(args)...);
}

template<typename Callable, typename... Args>
decltype(auto) call_v2(Callable &&F, Args &&... args) {
    if constexpr(std::is_same_v<std::invoke_result_t<Callable, Args...>, void>) {
        std::invoke(std::forward<Callable>(F), std::forward<Args>(args)...);
    } else {
        decltype(auto) ret(std::invoke(std::forward<Callable>(F), std::forward<Args>(args)...));
        return ret;
    }
}

template<template<typename...> class TT>
class AlmostAnyTmpl {
};

int main() {
    nprint(pi<double>)
    nprint(pi<float>)
    nprint(pi<long double>)
    int *a = nullptr;
    std::cout << sizeof(a) << std::endl;
    foo<uint64_t>();
    std::string s1 = "sname";
    Person p1(s1);
    Person p2("tmp");
    Person p3(p1);
    Person p4(std::move(p1));
    std::string s2 = "123";
    outR(s2);
    std::cout << IsPrime(9) << std::endl;
    std::invoke(print_num, 123);
    std::invoke([]() { std::cout << 123 << std::endl; });
    const Foo foo_class(123);
    std::invoke(&Foo::print_add, foo_class, 0);
    std::invoke(PrintSum(), 123);

    call([]() { std::cout << "call" << std::endl; });
    int num = 1;
    call_v2([](const int &num) { std::cout << num << std::endl; }, std::cref(num));


}
