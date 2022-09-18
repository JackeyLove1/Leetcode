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

// 获得n范围内所有质数
inline void init(int n) {
    cnt = 0;
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

inline int isPrime(int x) {
    int i;
    for (i = 2; i * i <= x; i++)
        if (x % i == 0)return 0;
    return 1;
}

char s[300];
int k;

int big_mod(char *s, int mod) {
    int q = 0;
    for (int i = 0; i < strlen(s); ++i) {
        q = (q * 10 + s[i] - '0') % mod;
    }
    return q;
}

int main() {
    init(N - 1);
    while (~scanf("%s %d", s, &k) && k) {
        int res = -1;
        for (int i = 0; i < cnt && primes[i] <= k; ++i) {
            res = big_mod(s, primes[i]);
            if (res == 0 && primes[i] < k) {
                printf("BAD %d\n", primes[i]);
                break;
            }
        }
        if (res != 0) {
            printf("GOOD\n");
        }
    }
    return 0;
}
