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

template<auto Val, typename T = decltype(Val)>
T foo();

template<typename T, auto MaxSize>
class Stack {
public:
    using size_type = decltype(MaxSize);

private:
    std::array<T, MaxSize> elems;
    size_type numElems;

public:
    Stack();

    void push(T const &elem);

    void pop();

    T const &top() const;

    bool empty() const { return numElems == 0; }

    size_type size() const {
        return numElems;
    }
};

template<decltype(auto) N>
class C {
};

void Print() {};

template<typename T, typename ... Types>
void Print(T head, Types... tail) {
    std::cout << head << std::endl;
    Print(tail...);
}

template<typename T>
void Print2(const T &t) {
    std::cout << t << std::endl;
}

template<typename T, typename ... Args>
void Print2(T head, Args... args) {
    Print2(head);
    Print2(args...);
}

template<typename T>
class AddSpace {
private:
    T const &ref;
public:
    AddSpace(T const &r) : ref(r) {}

    friend std::ostream &operator<<(std::ostream &os, AddSpace<T> s) {
        return os << s.ref << " ";
    }
};

template<typename ... Types>
void Print3(Types const &... args) {
    (std::cout << ...<< AddSpace(args)) << std::endl;
}

template<typename ... Args>
auto Sum(Args... args) {
    return (... + args);
}

class A {
public:
    A() = default;

    explicit A(int a_) : a(a_) {}

    int GetValue() const { return a; }

private:
    int a;
};

std::unique_ptr<A> make_A(int value = 0) {
    return std::make_unique<A>(value);
}

template<typename T1, typename ... TN>
constexpr bool isHomogeneous(T1, TN...) {
    return (std::is_same<T1, TN>::value && ...);
}


template<typename T1, typename T2>
constexpr bool isSame(T1, T2) {
    return std::is_same_v<T1, T2>;
}

template<typename T1, typename T2, typename... TN>
constexpr bool isSame(T2 t2, TN... tn) {
    return std::is_same_v<T1, T2> && isSame(tn ..., nullptr);
}

template<typename T>
void printDouble(T const &t) {
    std::cout << (t + t) << std::endl;
}

template<typename T, typename ... Args>
void printDouble(T const &t, Args const &... args) {
    printDouble(t);
    printDouble(args...);
}

int main() {
    const int a = 1;
    int b = 2;
    int c = 3;
    nprint((std::is_same<decltype(a), decltype(b)>::value))
    nprint((std::is_same<decltype(c), decltype(b)>::value))
    Print(1, "2", 3.0);
    Print2(1, "2", 3.0);
    Print3(1, "2", 3.0);
    nprint(Sum(1, 2, 3, 4, 5));
    std::future<void> future_hello_world =
            std::async(std::launch::async,
                       [&]() -> decltype(auto) { std::cout << "Hello, World!" << std::endl; });
    future_hello_world.wait();
    auto A = make_A(100);
    nprint(A->GetValue())
    std::array<int, 1> arrays{};
    for (const auto num: arrays) {
        nprint(num)
    }
    nprint(isHomogeneous(1, 2.0, "Hello"))
    nprint(isSame(2.0, "Hello"))
    nprint(isHomogeneous(1, 2, 3))
    nprint(isSame(2, 3))

    printDouble(1);
    printDouble(1, 2, 3);
    printDouble(4,std::string("5") ,6.0);
}