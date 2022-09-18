#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <numeric>
#include <cmath>

using namespace std;
// using sll = __int128;
using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;

static inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

inline int popcount(int x) {
    return __builtin_popcount(x);
}

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

constexpr int N = 1e4 + 10, M = 1250;
int primes[N];
PII factors[M];
bool st[N];
int cntf, cnt, cntd;

static set<int> ps;

// 获得n范围内所有质数
inline void init(int n) {
    memset(st, false, sizeof st);
    for (int i = 2; i <= n; ++i) {
        if (!st[i]) {
            primes[cnt++] = i;
            for (int j = 0; primes[j] <= n / i; ++j) {
                st[primes[j] * i] = true;
                if (i % primes[j] == 0) break;
            }
        }
    }
}

inline void get_factor(int d) {
    cntf = 0;
    // memset(factor, 0, sizeof factor);
    for (int i = 0; primes[i] <= d / primes[i]; ++i) {
        int p = primes[i];
        if (d % p == 0) {
            int s = 0;
            while (d % p == 0) ++s, d /= p;
            factors[++cntf] = {p, s};
        }
    }
    if (d > 1) factors[++cntf] = {d, 1};
}

ll solve(int n, int p) {
    return n < p ? 0 : (solve(n / p, p) + 1ll * (n / p));
}

int main() {
    fhj();
    init(N);
    for (int i = 0; i < cnt; ++i) {
        ps.insert(primes[i]);
    }
    int n;
    while (cin >> n && n) {
        const int end = n / 2;
        int res = 0;
        for (int i = 0; i < cnt && primes[i] <= end; ++i) {
            if (ps.count(n - primes[i])) ++res;
        }
        cout << res << endl;
    }
    return 0;
}