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

int n, mod;

inline ll cal(int x) {
    return 1l * x * (x + 1) * (2 * x + 1) / 6;
}

int main() {
    cin >> n;
    ll res = 0;
    int l = 0, r = 0;
    for (l = 1; l <= n; l = r + 1) {
        r = n / (n / l);
        res += (cal(r) - cal(l - 1)) * (n / l);
    }
    cout << res << endl;
    return 0;
}