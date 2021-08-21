#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>
#include <climits>
#include <queue>

using namespace std;

constexpr int N = 410, INF = 0x3f3f3f3f;

int f[N][N], g[N][N], s[N], w[N];
int n, k;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> k;
        w[i] = k, w[i + n] = k;
    }

    for (int i = 1; i <= 2 * n; i++) s[i] = s[i - 1] + w[i];
    memset(f, 0x3f, sizeof f);
    memset(g, -0x3f, sizeof g);
    for (int len = 1; len <= n; len++) {
        for (int l = 1, r; r = l + len - 1, r <= 2 * n; l++) {
            if (len == 1) f[l][l] = g[l][l] = 0;
            else {
                for (k = l; k < r; k++) {
                    f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r] + s[r] - s[l - 1]);
                    g[l][r] = max(g[l][r], g[l][k] + g[k + 1][r] + s[r] - s[l - 1]);
                }
            }
        }
    }

    int maxn = INT_MIN, minn = INT_MAX;
    for (int i = 1; i <= n; i++) {
        maxn = max(maxn, g[i][i + n - 1]);
        minn = min(minn, f[i][i + n - 1]);
    }
    cout << minn << endl << maxn << endl;
    return 0;
}