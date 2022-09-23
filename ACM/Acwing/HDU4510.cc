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


static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 110, M = 1250, INF = 0x3f3f3f3f;

int n, m;
int v1, v2, k;
int a[N], b[N], c[N];
ll f[N][N][6];

inline void solve() {
    memset(f, 0, sizeof f);
    cin >> n >> v1 >> v2 >> k;
    for (int i = 0; i < n; ++i) cin >> a[i] >> b[i] >> c[i];
    for (int i = 0; i < n; ++i) {
        for (int j = v1; j >= a[i]; --j) {
            for (int l = v2; l >= b[i]; --l) {
                for (int u = 5; u >= 1; --u) {
                    f[j][l][u] = std::max({f[i - a[i]][l][u], f[i][l - b[i]][u], f[i][l][u - 1]}) + c[i];
                }
            }
        }
    }
    cout << f[v1][v2][5] << endl;
}

int main() {
    fhj();
    int t;
    cin >> t;
    while (t--){
        solve();
    }
    return 0;
}