#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

using ll = int;
constexpr int N = 2002, MOD = 998244353;
using PIII = tuple<int, int, int>;
unordered_map<size_t, int> f;
int n, m, k;

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

int dp(int pos, int cnt, int pre) {
    if (pos > n) {
        return cnt == k;
    }
    auto p = make_tuple(pos, cnt, pre);
    auto h = hashValue(p);
    if (f.count(h)) return f[h];
    int ret = 0;
    for (int i = 1; i <= m; ++i) {
        ret = (ret + dp(pos + 1, cnt + (pre != i), i)) % MOD;
    }
    return f[h] = ret;
}

int main() {
    fhj();
    cin >> n >> m >> k;
    ll res = 0;
    for (int i = 1; i <= m; ++i) {
        res = (res + dp(2, 0, i)) % MOD;
    }
    cout << res << endl;
    return 0;
}
