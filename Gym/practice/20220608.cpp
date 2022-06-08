//
// Created by Jacky on 2022/6/8.
//

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <list>

using std::cout, std::endl;

template<typename T, unsigned N>
T sum(const T (&array)[N]) {
    T sum(0);
    for (auto i = 0; i < N; ++i) {
        sum += array[i];
    }
    return sum;
}

template<typename F, typename T, unsigned N>
class nth_derivative {
    using prev_derivative = nth_derivative<F, T, N - 1>;
public:
    nth_derivative(const F &f, const T &h) : h(h), fp(f, h) {}

    T operator()(const T &x) const {
        return (fp(x + h) - fp(x)) / h;
    }

private:
    T h;
    prev_derivative fp;
};

template<typename F, typename T>
class nth_derivative<F, T, 1> {
public:
    nth_derivative(const F &f, const T &h) : h(h), f(f) {}

    T operator()(const T &x) const {
        return (f(x + h) - f(x)) / h;
    }

private:
    T h;
    const F &f;
};

struct value_not_found {
};
struct value_not_found_twice {
};

// 静态多态和动态多态
template<typename Range, typename Value>
void print_interval(const Range &r, const Value &v, std::ostream &os = std::cout) {
    auto it = std::find(std::begin(r), std::end(r), v), it2 = it;
    if (it == std::end(r)) {
        // throw value_not_found;
        return;
    }
    ++it2;
    auto past = std::find(it2, std::end(r), v);
    if (past == std::end(r)) {
        // throw value_not_found_twice;
        return;
    }
    ++past;
    for (; it != past; ++it) {
        os << (*it) << " ";
    }
    os << '\n';
}

int main() {
    const int a1[] = {1, 2, 3};
    constexpr int a2[] = {1, 2, 3};
    double a3[] = {1.0, 2.0, 3.0, 4.0};
    cout << sum(a1) << endl;
    cout << sum(a2) << endl;
    cout << sum(a3) << endl;
    auto f = [](double x) -> auto {
        return std::sin(x) + std::cos(x);
    };
    nth_derivative<decltype(f), double, 3> d(f, 0.01);
    cout << d(1.0) << endl;
    std::vector<int> v1{1, 2, 3, 4, 5, 6, 1, 2, 3};
    print_interval(v1, 1);
    return 0;
}