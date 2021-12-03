// Author: Jacky
// Date: 2021-09-29
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>

using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

constexpr int MOD = 1e9 + 7;

int main() {
    fhj();
    int n;
    cin >> n;
    unordered_map<int, int> primes;
    while (n--) {
        int x;
        cin >> x;
        for (int i = 2; i <= x / i; ++i) {
            while (x % i == 0) {
                ++primes[i];
                x /= i;
            }
        }
        if (x > 1) ++primes[x];
    }
    ll res = 1;
    for (auto&[_, v] : primes) {
        res = res * (v+1) % MOD;
    }
    cout << res << endl;
    return 0;
}