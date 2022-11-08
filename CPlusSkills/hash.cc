#include <tuple>
#include <iostream>
#include <functional>
#include <type_traits>
template<typename Tuple, std::size_t... ids>
std::size_t tupleHash(Tuple const &tuple, std::index_sequence<ids...> const &);

template<typename T>
std::size_t hashValue(T const &value) {
    // SFINAE kicks in here for tuples.
    // There is no std::hash that works for tuples.
    // So this candidate will be ignored if you use a tuple.
    std::hash<T> hasher;
    return hasher(value);
}

template<typename... Args>
std::size_t hashValue(std::tuple<Args...> const &value) {
    return tupleHash(value, std::make_index_sequence<sizeof...(Args)>());
}

// Special case the empty tuple (as Args... can not be the empty list).
std::size_t hashValue(std::tuple<> const &value) {
    // Not an expert in hashing.
    // Do some appropriate thing to get a value;
    return 1;
}

template<typename Tuple, std::size_t... ids>
std::size_t tupleHash(Tuple const &tuple, std::index_sequence<ids...> const &) {
    // Not an expert in hashing.
    // Not sure 0 is a good seed (or this algorithm is good) solely here for demo purpose.
    std::size_t result = 0;
    for (auto const &hash: {hashValue(std::get<ids>(tuple))...}) {
        result ^= hash + 0x9e3779b9 + (result << 6) + (result >> 2);
    }
    return result;
};

int main()
{
    auto tp = std::make_tuple(1,2,"Loki");
    std::cout << hashValue(tp) << "\n";

    auto ttp = std::make_tuple(4,tp,8,tp);
    std::cout << hashValue(ttp) << "\n";

    auto et = std::make_tuple();
    std::cout << hashValue(et) << "\n";
}