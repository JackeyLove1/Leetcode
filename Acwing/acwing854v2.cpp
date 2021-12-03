#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <numeric>
#include <cmath>
#include <queue>

using namespace std;

constexpr int N = 220;

int n, m, k;
int d[N][N];

inline void init() {
    memset(d, 0x3f, sizeof d);
    for (int i = 1; i <= n; i++) d[i][i] = 0;
}

inline void floyed() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                d[i][j] = min(d[i][k] + d[k][j], d[i][j]);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> k;
    init();
    while (m--) {
        int x, y, z;
        cin >> x >> y >> z;
        d[x][y] = min(d[x][y], z);
    }
    floyed();
    while (k--) {
        int x, y;
        cin >> x >> y;
        if (d[x][y] >= 0x3f3f3f3f / 2) cout << "impossible" << endl;
        else cout << d[x][y] << endl;
    }
    return 0;
}