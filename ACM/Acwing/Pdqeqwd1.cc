#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e5 + 100;
int primes[N], cnt;
bool vis[N];
using bignum = __int128;

inline int get_primes(int n) {
    memset(vis, false, sizeof vis);
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) primes[cnt++] = i;
        for (int j = 0; j < cnt && 1ll * primes[j] * i <= n; ++j) {
            vis[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

inline int get(int n, int p) {
    int s = 0;
    while (n) s += n / p, n /= p;
    return s;
}

inline int get_cp(int n, int m, int p) {
    if (m > n) return 0;
    return get(n, p) - get(m, p) - get(n - m, p);
}

inline bignum qpow(bignum a, int b) {
    bignum res = 1;
    bignum base = a;
    while (b) {
        if (b & 1) res = res * base;
        base = base * base;
        b >>= 1;
    }
}

inline void mul(int C[], int p, int &len) {
    int t = 0;
    for (int i = 0; i < len; ++i) {
        t += C[i] * p;
        C[i] = t % 10;
        t /= 10;
    }
    while (t) {
        C[len++] = t % 10;
        t /= 10;
    }
}

inline void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}

int main() {
    fhj();
    int n, m;
    cin >> n >> m;
    get_primes(n);
    bignum res = 0;
    for (int i = 0; i < cnt; ++i) {
        int p = primes[i];
        int s = get_cp(n, m, p);
        while (s--) res += qpow(p, s);
    }
    print(res);
    cout << endl;
    return 0;
}

