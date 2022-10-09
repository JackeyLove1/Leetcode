#include<cmath>
#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<iomanip>
#include<vector>
#include<string>
#include<bitset>
#include<queue>
#include<map>
#include<set>

using namespace std;

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')f = -1;
        ch = getchar();
    }
    while (ch <= '9' && ch >= '0') {
        x = 10 * x + ch - '0';
        ch = getchar();
    }
    return x * f;
}

void print(int x) {
    if (x < 0)putchar('-'), x = -x;
    if (x >= 10)print(x / 10);
    putchar(x % 10 + '0');
}

const int N = 300100, P = 998244353;

inline int qpow(int x, int y) {
    int res(1);
    while (y) {
        if (y & 1) res = 1ll * res * x % P;
        x = 1ll * x * x % P;
        y >>= 1;
    }
    return res;
}

int r[N];

void ntt(int *x, int lim, int opt) {
    register int i, j, k, m, gn, g, tmp;
    for (i = 0; i < lim; ++i)
        if (r[i] < i)
            swap(x[i], x[r[i]]);
    for (m = 2; m <= lim; m <<= 1) {
        k = m >> 1;
        gn = qpow(3, (P - 1) / m);
        for (i = 0; i < lim; i += m) {
            g = 1;
            for (j = 0; j < k; ++j, g = 1ll * g * gn % P) {
                tmp = 1ll * x[i + j + k] * g % P;
                x[i + j + k] = (x[i + j] - tmp + P) % P;
                x[i + j] = (x[i + j] + tmp) % P;
            }
        }
    }
    if (opt == -1) {
        reverse(x + 1, x + lim);
        register int inv = qpow(lim, P - 2);
        for (i = 0; i < lim; ++i)
            x[i] = 1ll * x[i] * inv % P;
    }
}

int A[N], B[N], C[N];

char a[N], b[N];

int main() {
    register int i, lim(1), n;
    scanf("%s", &a);
    n = strlen(a);
    for (i = 0; i < n; ++i) A[i] = a[n - i - 1] - '0';
    while (lim < (n << 1)) lim <<= 1;
    scanf("%s", &b);
    n = strlen(b);
    for (i = 0; i < n; ++i) B[i] = b[n - i - 1] - '0';
    while (lim < (n << 1)) lim <<= 1;
    for (i = 0; i < lim; ++i)
        r[i] = (i & 1) * (lim >> 1) + (r[i >> 1] >> 1);
    ntt(A, lim, 1);
    ntt(B, lim, 1);
    for (i = 0; i < lim; ++i)
        C[i] = 1ll * A[i] * B[i] % P;
    ntt(C, lim, -1);
    int len(0);
    for (i = 0; i < lim; ++i) {
        if (C[i] >= 10)
            len = i + 1,
            C[i + 1] += C[i] / 10, C[i] %= 10;
        if (C[i]) len = max(len, i);
    }
    while (C[len] >= 10)
        C[len + 1] += C[len] / 10, C[len] %= 10, len++;
    for (i = len; ~i; --i)
        putchar(C[i] + '0');
    puts("");
    return 0;
}