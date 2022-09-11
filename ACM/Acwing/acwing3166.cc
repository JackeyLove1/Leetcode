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

constexpr int N = 1e3 + 100, MOD = 1e9 + 7;
int f[N][N];

int main() {
    int n, m;
    cin >> n >> m;
    memset(f, 0, sizeof f);
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            f[i][j] = (f[i - 1][j - 1] + (ll) j * f[i - 1][j] % MOD) % MOD;
        }
    }
    cout << f[n][m] << endl;
    return 0;
}