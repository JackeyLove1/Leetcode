#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>
#include <numeric>
#include <array>

using namespace std;

using ll = long long;
using PII = pair<int, int>;

const int N = 1e6 + 10, M = 1250;
int primes[N];
bool st[N];
int cnt;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

inline ll qsm(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1) res = (res * a) % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

inline ll qsc(ll a, ll b, ll mod) {
    ll res = 0;
    while (b) {
        if (b & 1) res = (res + a) % mod;
        a = a * 2 % mod;
        b >>= 1;
    }
    return res;
}

ll n, m;
constexpr ll mod = 10000000007LL;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%lld%lld", &n, &m);
        ll res = 0, x;
        for (int i = 0; i < n; ++i) {
            scanf("%lld", &x);
            x %= mod;
            res = (res + qsm(x, m, mod)) % mod;
        }
        printf("%lld\n", res);
    }
    return 0;
}