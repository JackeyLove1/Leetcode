#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ll = long long;
constexpr int N = 2000 + 2, MOD = 998244353;
int n, m, k;
ll f[N][N];

// f[i][j] = f[i-1][j] + f[i-1][j-1] *(m -1)
int main() {
    fhj();
    cin >> n >> m >> k;
    memset(f, 0, sizeof 0);
    for (int i = 1; i <= n; ++i) f[i][0] = m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            f[i][j] = (f[i - 1][j] % MOD + f[i - 1][j - 1] * (m - 1) % MOD) % MOD;
        }
    }
    cout << f[n][k] << endl;
    return 0;
}