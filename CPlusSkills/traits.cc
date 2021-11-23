#include <iostream>
#include <functional>
#include <tuple>

// Message Registration

struct is_true {
};
struct is_false {
};

template<typename T>
struct traits {
    typedef is_false is_raw;
};

template<>
struct traits<char> {
    typedef is_true is_raw;
};

template<>
struct traits<int> {
    typedef is_true is_raw;
};

template<>
struct traits<std::nullptr_t> {
    typedef is_true is_raw;
};

// for test
template<typename RawType>
void func(RawType);

template<>
void func(is_false) {
    std::cout << "this is not raw type" << std::endl;
}

template<>
void func(is_true) {
    std::cout << "this is raw type" << std::endl;
}

template<typename T>
void DoSomething(T t) {
    func(typename traits<T>::is_raw());
}

int main() {
    int a = 1;
    DoSomething(a);
    double b = 2;
    DoSomething(b);
}