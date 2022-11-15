// practice 2022-11-13
// author: fanhj
// 数论分块
// #pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 2e7 + 100, M = 65, INF = 0x3f3f3f3f;
using ll = long long;
int n, m, k;

int main() {
    fhj();
    cin >> n >> k;
    ll sum1 = 1ll * n * k;
    ll sum2 = 0;
    int l = 1, r = 0;
    while (l <= n) {
        if (k / l) r = std::min(k / (k / l), n);
        else r = n;
        sum2 += 1ll * (l + r) * (r - l + 1) * (k / l) / 2;
        l = r + 1;
    }
    cout << sum1 - sum2 << endl;
    return 0;
}