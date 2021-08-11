#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
#include <set>
#include <list>
#include <unordered_map>
#include <unordered_set>

using namespace std;

constexpr int N = 1e3 + 10;
int n, m;
int v[N], w[N];
int f[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> v[i] >> w[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k * v[i] <= j; k++) {
                f[i][j] = max(f[i][j], f[i - 1][j - v[i] * k] + w[i] * k);
            }
        }
    }
    cout << f[n][m] << endl;
    return 0;
}