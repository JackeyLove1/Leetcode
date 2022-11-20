ll exgcd(ll a, ll b, ll &x, ll &y)// 拓欧
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}
ll inv(ll a, ll p)
{
    ll x, y;
    if (exgcd(a, p, x, y) != 1) // 无解的情形
        return -1;
    return (x % p + p) % p;
}

// 多次对不同的p使用需要清空Inv数组
ll Inv[MAXN] = {0, 1};
inline ll mod(ll a, ll p)
{
    return (a % p + p) % p;
}
ll inv(ll a, ll p)
{
    if (Inv[a])
        return Inv[a];
    Inv[a] = mod(-p / a * inv(p % a, p), p);
    return Inv[a];
}

/*
// 在 O(n) 时间内求出 0 到 n 之间所有数在 (modp) 意义下的乘法逆元。
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int maxn = 1000005;
const ll MOD = 1000000007;

ll qpw(ll a, ll b) {
    ll ans = 1;
    while (b) {
        if (b & 1) ans = ans * a % MOD, b--;
        a = a * a % MOD;
        b >>= 1;
    }
    return ans;
}

ll inv[maxn + 1];
void pre_process() {
    inv[1] = 1;
    for (int i = 2; i <= maxn; i++)
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
}
*/