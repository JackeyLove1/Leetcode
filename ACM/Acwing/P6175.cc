// #pragma GCC optimize(2)
#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

int n, m;
constexpr int N = 2e3 + 100, INF = 0x3f3f3f3f;
using ll = long long;
int w[N][N], d[N][N];

int main() {
    cin >> n >> m;
    memset(w, 0x3f, sizeof w);
    for (int i = 1; i <= n; ++i) w[i][i] = 0;
    int ans = INF;
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        w[a][b] = w[b][a] = c;
    }
    memcpy(d, w, sizeof w);
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i < k; ++i) {
            for (int j = i + 1; j < k; ++j) {
                if (w[j][k] != INF && w[k][i] != INF) {
                    ans = std::min(ans, d[i][j] + w[j][k] + w[k][i]);
                }
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (d[i][k] != INF && d[k][j] != INF) {
                    d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }
    if (ans != INF) cout << ans << endl;
    else cout << "No solution." << endl;
    return 0;
}