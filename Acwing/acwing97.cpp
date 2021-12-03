// Author: Jacky
// Time: 2021-09-17
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for (auto &n : num) {
            cout << n << " ";
        }
        cout << endl;
    }
    // cout << "ending ... " << endl;
}

using ll = long long;
ll a, b;
constexpr int MOD = 9901;

ll qsm(ll a, ll b) {
    ll res = 1 % MOD;
    while (b) {
        if (b & 1) res = a * res % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

ll sum(int p, int c) {
    if (c == 0) return 1;
    if (c & 1) {
        return (1 + qsm(p, (c + 1) >> 1)) % MOD * sum(p, (c - 1) >> 1) % MOD;
    } else {
        return (((1 + qsm(p, c >> 1)) * sum(p, c / 2 - 1)) % MOD + qsm(p, c)) % MOD;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> a >> b;
    if (a == 0) {
        cout << 0 << endl;
        return 0;
    }
    int ans = 1;
    for (int i = 2; i <= a; ++i) {
        int s = 0;
        while (a % i == 0) {
            s++;
            a /= i;
        }
        if (s) {
            ans = ans * sum(i, s * b) % MOD;
        }
    }
    cout << ans << endl;
    return 0;
}