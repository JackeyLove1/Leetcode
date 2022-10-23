#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 100000 + 100;
using ll = long long;

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

inline ll inv(ll a, ll p) {
    ll x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}

// a是模数数组，b是余数数组，n是数组长度
inline ll CRT(ll a[], ll b[], ll n) {
    ll p = 1, x = 0;
    for (int i = 0; i < n; ++i)
        p *= a[i];
    for (int i = 0; i < n; ++i) {
        ll r = p / a[i];
        x += (b[i] * r * inv(r, a[i])) % p;
    }
    return x % p;
}

int n;
ll a[N], b[N];

int main() {
    fhj();
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
    }
    cout << CRT(a, b, n) << endl;
    return 0;
}