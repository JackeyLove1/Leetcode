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

using ll = long long;

const int N = 1e6 + 10, mod = 1e9 + 7;

int n;
bool st[N];
int primes[N], cnt;

void get_primes(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!st[i]) primes[cnt++] = i;
        for (int j = 0; primes[j] * i <= n; ++j) {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

// 计算素约数个数
int solve() {
    get_primes(n);
    ll res = 1;
    for (int i = 0; i < cnt; ++i) {
        int p = primes[i];
        int s = 0;
        for (int j = n; j; j /= p) s += j / p;
        res = (ll) (2 * s + 1) * res % mod;
    }
    return res;
}

int main() {
    fhj();
    cin >> n;
    cout << solve << endl;
    return 0;
}