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

int main() {
    fhj();
    ll a, b, p;
    cin >> a >> b >> p;
    printf("%lld^%lld mod %lld=%lld\n", a, b, p, qpow(a, b, p));
    return 0;
}