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
using sll = __int128;
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

constexpr int N = 5000007;

ll s[N], primes[N];
ll f[N];
int n, m, cnt;
ll phi[N];
bool st[N];

void get_phis(int n) {
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!st[i]) {
            primes[cnt++] = i;
            phi[i] = i - 1;
        }
        for (int j = 0; primes[j] <= n / i; j++) {
            auto t = primes[j] * i;
            st[t] = true;
            if (i % primes[j] == 0) {
                phi[t] = phi[i] * primes[j];
                break;
            }
            phi[t] = phi[i] * (primes[j] - 1);
        }
    }
}

int main() {
    get_phis(N - 5);
    for (int i = 1; i <= N - 1; ++i) {
        for (int j = i * 2; j <= N; j += i) {
            f[j] += i * phi[j / i];
        }
    }
    for (int i = 1; i <= N - 1; ++i) {
        s[i] = s[i - 1] + f[i];
    }
    while (cin >> n && n) {
        cout << (s[n] * 2 + (1 + n) * n / 2) << endl;
    }
    return 0;
}