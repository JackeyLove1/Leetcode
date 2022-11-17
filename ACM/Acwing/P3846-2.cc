#include <bits/stdc++.h>

using namespace std;
constexpr int N = 1e5 + 100;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ll = long long;

inline ll qpow(ll a, ll b, ll p) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

inline ll BSGS(ll a, ll b, ll p) {
    unordered_map<ll, int> h;
    a %= p, b %= p;
    if (b == 1) return 0;
    ll m = static_cast<ll>(std::sqrt(p)) + 1;
    ll t = b;
    h[b] = 0;
    for (int j = 1; j <= m; ++j) {
        t = t * a % p;
        h[t] = j;
    }
    auto mi = qpow(a, m, p);
    t = 1;
    for (int i = 1; i <= m; ++i) {
        t = t * mi % p;
        if (h.count(t)) {
            return i * m - h[t];
        }
    }
    return -1;
}

int main() {
    int a, p, b;
    cin >> p >> a >> b;
    int res = BSGS(a, b, p);
    if (res == -1) puts("no solution");
    else cout << res << endl;
    return 0;
}