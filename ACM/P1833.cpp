#include <climits>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

constexpr int N = 1e6 + 100;

struct good {
    int v, w, s;
};
int nx, ny, ex, ey, n, m;
int a, b, c;
int f[N];

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    scanf("%d:%d%d:%d%d", &nx, &ny, &ex, &ey, &n);
    m = (ex * 60 + ey) - (nx * 60 + ny);
    vector<good> goods;
    for (int i = 1; i <= n; i++) {
        cin >> a >> b >> c;
        if (!c) {
            goods.push_back({a, b, 0});
        }
        for (int k = 1; k <= c; k *= 2) {
            goods.push_back({a * k, b * k, 1});
            c -= k;
        }
        if (c) {
            goods.push_back({a * c, b * c, 1});
        }
    }

    for (auto &g : goods) {
        int v = g.v, w = g.w, s = g.s;
        if (!s) { // 完全背包问题
            for (int j = v; j <= m; j++) {
                f[j] = max(f[j], f[j - v] + w);
            }
        } else { // 01 背包问题
            for (int j = m; j >= v; j--) {
                f[j] = max(f[j], f[j - v] + w);
            }
        }
    }

    cout << f[m] << endl;
    return 0;
}