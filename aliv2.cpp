#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

int n, m, p;

constexpr int N = 600, INF = 1e9;

int g[N][N], w[N];
int f[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> p;
    for (int i = 1; i <= n; i++) cin >> w[i];

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) g[i][j] = 0;
            else g[i][j] = INF;
        }
    }

    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = g[b][a] = c;
    }

    // floyed
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }

    int idx = n, res = 0;
    for (int i = 1; i <= n; i++) {
        memset(f, 0, sizeof f);
        for (int j = 1; j <= n; j++) {
            for (int k = 0; k <= p; k++) {
                int gas = 2 * g[i][j];
                if (k >= gas) {
                    f[j][k] = max(f[j - 1][k], f[j - 1][k - gas] + w[j]);
                } else {
                    f[j][k] = f[j - 1][k];
                }
            }
        }
        if (f[n][p] > res) {
            res = f[n][p];
            idx = i;
        }
    }

    cout << idx << ' ' << res << endl;
    return 0;
}