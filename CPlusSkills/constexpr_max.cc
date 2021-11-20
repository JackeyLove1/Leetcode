#include <iostream>

template<typename T>
constexpr T constexpr_max(T a) {
    return a;
}

template<typename T, typename... Ts>
constexpr T constexpr_max(T a, T b, Ts... ts) {
    return b < a ? constexpr_max(a, ts...) : constexpr_max(b, ts...);
}

int main() {
    std::cout << constexpr_max(1, 2, 3, 4, 5) << std::endl;

}