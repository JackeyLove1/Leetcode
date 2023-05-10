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

template<typename T1, typename T2>
std::common_type_t<T1, T2> max(T1 a, T2 b) {
    return b < a ? a : b;
}

template<typename T1, typename T2>
constexpr auto min(T1 a, T2 b) {
    return b > a ? a : b;
}

#define nprint(x) std::cout << (x) << std::endl;
#define cprint(container) std::for_each((container).begin(), (container).end(), [](const auto& e){nprint(e)});
#define test_print(...) do {\
        std::initializer_list<std::decay_t<decltype(*std::begin({__VA_ARGS__}))>> container{__VA_ARGS__};\
        cprint(container);\
    } while (false);\


using Tag = std::pair<std::string, std::string>;
using Tags = std::vector<Tag>;

static inline std::string TagToString(const Tags &tags) {
    return std::accumulate(tags.begin(), tags.end(), std::string{},
                           [](const auto &result, const auto &tag) -> decltype(auto) {
                               return result + tag.first + tag.second;
                           });
}

static std::string TagToString2(const Tags &tags) {
    std::string output;
    output.reserve(200);
    for (const auto &t: tags) {
        output += t.first + t.second;
    }
    return output;
}

static std::string TagToString3(const Tags &tags) {
    std::string output{};
    output.reserve(200);
    std::for_each(tags.begin(), tags.end(), [&](const Tag &tag) { output += tag.first + tag.second; });
    return output;
}

template<int N>
class Fib {
public:
    static const int value = Fib<N - 1>::value + Fib<N - 2>::value;
};

template<>
class Fib<0> {
public:
    static const int value = 0;
};

template<>
class Fib<1> {
public:
    static const int value = 1;
};

template<int ... Args>
struct Sum {
    static const int value = 0;
};

template<int head, int ... tail>
struct Sum<head, tail...> {
    static const int value = head + Sum<tail...>::value;
};

template<int N>
struct Sum2 {
    static const int value = Sum2<N - 1>::value + N;
};

template<>
struct Sum2<0> {
    static const int value = 0;
};

template<int a, int b>
struct GCD {
    static const int value = GCD<b, a % b>::value;
};

template<int a>
struct GCD<a, 0> {
    static const int value = a;
};

template<int... values>
struct IntList {
    static const int size = sizeof...(values);
};

template<int head, typename tail>
struct IntCons;

template<int head, int... tail>
struct IntCons<head, IntList<tail...>> {
    typedef IntList<head, tail...> reType;
};

template<typename lst>
struct Length;

template<int... values>
struct Length<IntList<values...>> {
    static const int value = sizeof...(values);
};

template<typename lst, int index>
struct Element;

template<int head, int... tail, int index>
struct Element<IntList<head, tail...>, index> {
    static const int value = Element<IntList<tail...>, index - 1>::value;
};

template<int head, int... tail>
struct Element<IntList<head, tail...>, 0> {
    static const int value = head;
};

template<int n>
class IntBubbleSortC {
    template<int i, int j>
    static inline void IntSwap(int *data) { // 比较和交换两个相邻元素
        if (data[i] > data[j]) std::swap(data[i], data[j]);
    }

    template<int i, int j>
    static inline void IntBubbleSortLoop(int *data) { // 一次冒泡
        IntSwap<j, j + 1>(data);
        IntBubbleSortLoop<j < i - 1 ? i : 0, j < i - 1 ? (j + 1) : 0>(data);
    }

    template<>
    static inline void IntBubbleSortLoop<0, 0>(int *) {}

public:
    static inline void sort(int *data) {
        IntBubbleSortLoop<n - 1, 0>(data);
        IntBubbleSortC<n - 1>::sort(data);
    }
};

template<>
class IntBubbleSortC<0> {
public:
    static inline void sort(int *data) {}
};


int main() {
    std::cout << max(1, 2) << std::endl;
    std::cout << max(1.0, 2.0) << std::endl;
    nprint(min(1.0, 2.0))
    nprint(min(1, 2))
    std::vector<int> vec(10);
    std::iota(vec.begin(), vec.end(), 0);
    nprint(std::accumulate(vec.begin(), vec.end(), 0))
    std::vector<int> diff(vec.size());
    std::adjacent_difference(vec.begin(), vec.end(), diff.begin());
    cprint(diff)
    nprint(std::count_if(vec.begin(), vec.end(), [](const auto &e) { return e % 2; }))
    test_print(1, 2, 3);
    vec.erase(std::remove(vec.begin(), vec.end(), 3), vec.end());
    auto iter = std::find(vec.begin(), vec.end(), 3);
    nprint(iter == vec.end())
    Tags tags{{"id",      "1"},
              {"cluster", "2"}};
    nprint(TagToString(tags))
    nprint(TagToString2(tags))
    nprint(TagToString3(tags))
    Tags tags2{};
    nprint(TagToString(tags2))
    nprint(TagToString2(tags2))
    nprint(TagToString3(tags2))
    nprint(Fib<5>::value)
    const int res0 = Sum<1, 2, 3, 4, 5>::value;
    nprint(res0)
    const int res1 = Sum2<5>::value;
    nprint(res1)
    const int res2 = GCD<2, 5>::value;
    nprint(res2)

    int data[4] = {3, 4, 2, 1};
    IntBubbleSortC<4>::sort(data); // 如此调用
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
        nprint(data[i]);
    }
}