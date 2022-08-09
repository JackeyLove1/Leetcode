#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <unordered_set>


using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;
constexpr int N = 1e5 + 1000;
int e[N], h[N], ne[N], w[N], idx = 0;

inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

map<int, int> primes;

inline void getPrimes(int x) {
    for (int i = 2; i <= x / i; i++) {
        if (x % i == 0) {
            int s = 0;
            while (x % i == 0) {
                x /= i;
                s++;
            }
            primes.emplace(i, s);
            // cout << i << " " << s << endl;
        }
    }
    if (x != 1) {
        primes.emplace(x, 1);
        // cout << x << " " << 1 << endl;
    }
    // cout << endl;
}

int main() {
    fhj();
    int n;
    cin >> n;
    getPrimes(n);
    if (primes.begin()->first == n){
        cout << n << " " << 0 << endl;
        return 0;
    }
    int value = 1, times = 0;
    int maxCnt = 0;
    for (const auto &[k, v]: primes) {
        value *= k;
        maxCnt = max(maxCnt, v);
        // cout << "k: " << k <<" v: " << v << endl;
    }
    // cout << maxCnt << endl;
    while (std::pow(2, times) < maxCnt) ++times;
    for (const auto &[k, v]: primes){
        if (v != std::pow(2, times)) {
            times++;
            break;
        }
    }
    cout << value << " " << times << endl;
    return 0;
}