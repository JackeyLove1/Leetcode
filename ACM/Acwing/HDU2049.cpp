#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

const int N = 23, mod = 100003;

int fact[N], infact[N];
using LL = long long;

int qmi(int a, int k) {
    int res = 1;
    while (k) {
        if (k & 1) res = (LL) res * a % mod;
        a = (LL) a * a % mod;
        k >>= 1;
    }
    return res;
}

// 求组合数
int C(int a, int b) {
    if (a < b) return 0;
    return (LL) fact[a] * infact[a - b] % mod * infact[b] % mod;
}

// 求排列数
int P(int a, int b) {
    if (a < b) return 0;
    return (LL) fact[a] * infact[a - b] % mod;
}

int f[N];
int n, m;

void init() {
    // 初始化求解
    fact[0] = infact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = (LL) fact[i - 1] * i % mod;
        infact[i] = (LL) infact[i - 1] * qmi(i, mod - 2) % mod;
    }
    f[0] = 1, f[1] = 0, f[2] = 1;
    for (int i = 3; i < N; ++i) {
        f[i] = (i - 2) * (f[i - 1] + f[i - 2]);
    }
}

inline int solve(int a, int b) {
    return C(a, b) * f[b];
}

int main() {
    fhj();
    int t;
    init();
    cin >> t;
    while (t--) {
        cin >> n >> m;
        cout << solve(n, m) << endl;
    }
    return 0;
}