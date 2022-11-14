// practice 2022-11-13
// author: fanhj
// z-algorithm
#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 2e7 + 100, M = 65, INF = 0x3f3f3f3f;

int z[N], p[N], n, m;
char s[N], t[N];

inline void get_z(const char *s, int n) {
    z[1] = n; // 从1开始
    for (int i = 2, l, r = 0; i <= n; ++i) {
        if (i <= r) z[i] = std::min(z[i - l + 1], r - i + 1); // 利用前面以及匹配的结果
        while (s[1 + z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
}

inline void get_p(const char *s, int n, const char *t, int m) {
    // s为模式串，t为匹配串
    for (int i = 1, l, r = 0; i <= m; ++i) {
        if (i <= r) p[i] = std::min(z[i - l + 1], r - i + 1);
        while (1 + p[i] <= n && i + p[i] <= m && s[1 + p[i]] == t[i + p[i]]) ++p[i];
        if (i + p[i] - 1 > r) l = i, r = i + p[i] - 1;
    }
}

using ll = long long;

inline void solve() {
    ll res = 0;
    for (int i = 1; i <= n; ++i) {
        res ^= 1ll * (z[i] + 1) * i;
        // cout << z[i] <<" ";
    }
    // cout << endl;
    cout << res << endl;
    res = 0;
    for (int i = 1; i <= m; ++i) {
        res ^= 1ll * (p[i] + 1) * i;
        // cout << p[i] <<" ";
    }
    // cout << endl;
    cout << res << endl;
}

int main() {
    scanf("%s%s", t + 1, s + 1);
    n = strlen(s + 1), m = strlen(t + 1);
    memset(z, 0, sizeof z);
    memset(p, 0, sizeof p);
    get_z(s, n);
    get_p(s, n, t, m);
    solve();
    return 0;
}