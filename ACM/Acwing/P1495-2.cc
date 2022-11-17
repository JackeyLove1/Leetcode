#include <bits/stdc++.h>

using namespace std;
constexpr int N = 1e5 + 100;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ll = long long;
ll n, a[20], b[20];

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll x1, y1, d;
    d = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - a / b * y1;
    return d;
}

ll CRT(ll m[], ll r[]) {
    ll M = 1, ans = 0;
    for (int i = 1; i <= n; ++i) M *= m[i];
    for (int i = 1; i <= n; ++i) {
        ll c = M / m[i];
        ll x, y;
        auto d = exgcd(c, m[i], x, y);
        ans = (ans + c * x * r[i] % M) % M;
    }
    return (ans % M + M) % M;
}

int main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lld%lld", a + i, b + i);
    printf("%lld\n", CRT(a, b));
    return 0;
}