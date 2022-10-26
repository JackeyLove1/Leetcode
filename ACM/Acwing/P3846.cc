#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ll = long long;

inline ll read() {
    ll ans = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c)) {
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return ans;
}

const ll INF = 1e8;

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

inline ll qsm(ll a, ll b, ll p) {
    ll res = 1 % p;
    while (b) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

ll bsgs_qsm(ll a, ll b, ll p) {
    std::map<ll, ll> hash;
    b %= p;
    ll t = std::sqrt(p) + 1;
    for (int i = 0; i < t; ++i) {
        hash[b * qsm(a, i, p) % p] = i;
    }
    a = qsm(a, t, p);
    if (!a) return b == 0 ? 1 : -1;//特判
    for (int i = 1; i <= t; ++i) {//在Hash表中查找是否有i对应的j值
        ll val = qsm(a, i, p);
        int j = hash.find(val) == hash.end() ? -1 : hash[val];
        if (j >= 0 && i * t - j >= 0) return i * t - j;
    }
    return -1;//无解返回-1
}

ll bsgs(ll a, ll b, ll p) {
    if (1 % p == b % p) return 0;
    ll k = sqrt(p) + 1;
    std::map<ll, ll> hash;
    for (ll i = 0, j = b % p; i < k; i++) {
        hash[j] = i;
        j = (ll) j * a % p;
    }
    ll ak = 1;
    for (ll i = 0; i < k; i++) ak = (ll) ak * a % p;
    for (ll i = 1, j = ak; i <= k; i++) {
        if (hash.count(j)) return i * k - hash[j];
        j = (ll) j * ak % p;
    }
    return -INF;
}

ll exbsgs(ll a, ll b, ll p) {
    b = (b % p + p) % p;
    if (1 % p == b % p) return 0;
    ll x, y;
    ll d = exgcd(a, p, x, y);
    if (d > 1) {
        if (b % d) return -INF;
        exgcd(a / d, p / d, x, y);
        return exbsgs(a, (ll) b / d * x % (p / d), p / d) + 1;
    }
    return bsgs_qsm(a, b, p);
}

int main() {
    fhj();
    ll a, p, b;
    cin >> p >> a >> b;
    int res = bsgs(a, b, p);
    if (res < 0) puts("no solution");
    else cout << res << endl;
    return 0;
}
