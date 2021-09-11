#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <unordered_map>
#include <bitset>
#include <cstring>
#include <queue>

using namespace std;

constexpr int N = 150;
int f[N][N], g[N][N];
int n;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> g[i][j];
        }
    }
    int maxn = -1e9;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            f[i][j] = f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1] + g[i][j];
            maxn = max(f[i][j], maxn);
        }
    }
    for (int x1 = 1; x1 <= n; ++x1) {
        for (int y1 = 1; y1 <= n; ++y1) {
            for (int x2 = 1; x2 < x1; ++x2) {
                for (int y2 = 1; y2 < y1; ++y2) {
                    maxn = max(maxn, f[x1][y1] - f[x2 - 1][y1] - f[x1][y2 - 1] + f[x2 - 1][y2 - 1]);
                }
            }
        }
    }

    cout << maxn << endl;
    return 0;
}