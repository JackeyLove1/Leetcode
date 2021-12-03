#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <unordered_map>
#include <list>
#include <cmath>

using namespace std;

constexpr int N = 1e3 + 100;
int n, m;
int v[N], w[N];
int f[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> v[i] >> w[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= 2; k++) {
                if (j >= k * v[i]) {
                    f[i][j] = max(f[i][j], f[i - 1][j - k * v[i]] + k * w[i]);
                }
            }
        }
    }
    cout << f[n][m] << endl;
    return 0;
}