#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <numeric>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

const int MOD = 200907;

using ll = long long;

inline ll qsm(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1) res = (res * a) % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

inline ll qsc(ll a, ll b, ll mod) {
    ll res = 0;
    while (b) {
        if (b & 1) res = (res + a) % mod;
        a = a * 2 % mod;
        b >>= 1;
    }
    return res;
}

int main() {
    fhj();
    int T;
    cin >> T;
    while (T--) {
        ll a, b, c, k;
        cin >> a >> b >> c >> k;
        if (b - a == c - b) {
            ll diff = b - a;
            cout << (a + qsc(diff, k - 1, MOD)) % MOD << endl;
        } else {
            ll diff = b / a;
            cout << (a * qsm(diff, k - 1, MOD)) % MOD << endl;
        }
    }
    return 0;
}