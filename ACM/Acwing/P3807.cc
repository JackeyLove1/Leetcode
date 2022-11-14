
#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e5 + 100;
using ll = long long;
ll f[N], g[N];

inline ll qpow(ll a, int b, int p) {
    ll res = 1;
    while (b) {
        if (b & 1) res = (res * a) % p;
        a = (a * a) % p;
        b >>= 1;
    }
    return res;
}

inline void init(int p) {
    memset(f, 0, sizeof f);
    memset(g, 0, sizeof g);
    f[0] = g[0] = 1;
    for (int i = 1; i <= p; ++i) {
        f[i] = f[i - 1] * i % p;
        g[i] = g[i - 1] * qpow(i, p - 2, p) % p;
    }
}

inline ll getC(int n, int m, int p) {
    if (m > n) return 0;
    return f[n] * g[m] * g[n - m] % p;
}

inline ll Lucas(ll n, ll m, int p) {
    if (m == 0) return 1;
    return Lucas(n / p, m / p, p) * getC(n % p, m % p, p) % p;
}

inline ll solve(ll n, ll m, int p) {
    return Lucas(n, m, p);
}

int main() {
    fhj();
    int T;
    cin >> T;
    while (T--) {
        ll n, m, p;
        cin >> n >> m >> p;
        init(p);
        cout << solve(n + m, n, p) << endl;
    }
    return 0;
}
