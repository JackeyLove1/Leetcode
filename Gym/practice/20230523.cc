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
#include <algorithm>
#include <initializer_list>
#include <experimental/coroutine>
#include <boost/variant.hpp>
#include <boost/range.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>

template<typename ... Types>
class Tuple {
public:
    static constexpr std::size_t length = sizeof ... (Types);
};

template<typename ... Types>
class MyTuple : public Tuple<Types...> {

};

template<typename T>
bool f(T p) {
    if constexpr(sizeof(T) <= sizeof(long long)) {
        return p > 0;
    } else {
        return p.compare(0) > 0;
    }
}

template<bool b>
struct Dispatch {
    template<typename T>
    static bool f(T p) {
        return p.compare(0) > 0;
    }
};

template<>
struct Dispatch<true> {
    template<typename T>
    static bool f(T p) {
        return p > 0;
    }
};

template<typename T>
bool f2(T p) {
    return Dispatch<sizeof(T) <= sizeof(long long)>::f(p);
}

bool g(int n) {
    return f2(n);
}

#define nprint(x) std::cout << (x) << std::endl;


template<typename Head, typename ... Tails>
void print(Head &&h, Tails &&...tails) {
    std::cout << std::forward<Head>(h) << std::endl;
    if constexpr(sizeof ... (tails) > 0) {
        print(std::forward<Tails>(tails)...);
    }
}

template<typename Container>
void print(Container &container) {
    std::for_each(container.begin(), container.end(), [](const auto &num) {
        std::cout << num << std::endl;
    });
}

// Default Policy - SumPolicy
template<typename AccT, typename T>
struct SumPolicy {
    static void accumulate(AccT& total, T const& value) {
        total += value;
    }
};

// Default Traits - AccumulationTraits
template<typename T>
struct AccumulationTraits {
    using AccT = T;
    static AccT zero() {
        return AccT{};
    }
};

// accum function
template<typename T,
        template<typename, typename> class Policy = SumPolicy,
        typename Traits = AccumulationTraits<T>>
auto accum(T const* beg, T const* end) {
    using AccT = typename Traits::AccT;
    AccT total = Traits::zero();
    while (beg != end) {
        Policy<AccT, T>::accumulate(total, *beg);
        ++beg;
    }
    return total;
}

// Custom Policy - MultiplyPolicy
template<typename AccT, typename T>
struct MultiplyPolicy {
    static void accumulate(AccT& total, T const& value) {
        total *= value;
    }
};

// Custom Traits - DoubleAccumulationTraits
template<typename T>
struct DoubleAccumulationTraits {
    using AccT = double;
    static AccT zero() {
        return AccT{};
    }
};

int main() {
    MyTuple<int, float> t2;
    std::cout << g(1) << std::endl;
    print(1, 2.0, "3", static_cast<long>(4));
    std::vector<int> vec{1, 2, 3, 4, 5};
    nprint(boost::size(vec));
    print(vec);
    print(1);
    auto reverse_range = vec | boost::adaptors::reversed;
    print(reverse_range);
    auto transformed_range = vec | boost::adaptors::transformed([](auto num){return num * 2;});
    print(transformed_range);
    auto filterd_range = vec | boost::adaptors::filtered([](auto num){return num %2;});
    print(filterd_range);
    auto strided_range = vec | boost::adaptors::strided(2);
    print(strided_range);

    int numbers[] = {1, 2, 3, 4, 5};

    // Using default policy (SumPolicy) and default traits (AccumulationTraits)
    auto result1 = accum(numbers, numbers + 5);
    std::cout << "Default Policy and Traits: " << result1 << std::endl; // Output: 15
}
