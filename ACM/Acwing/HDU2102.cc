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
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <functional>
#include <tuple>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using PII = pair<int, int>;


static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}


constexpr int N = 110, M = 65, INF = 0x3f3f3f3f, MOD = 1e4;
int vis[2][11][11];
char map[2][11][11];
int n, m;
constexpr int dx[]{-1, 0, 1, 0}, dy[]{0, 1, 0, -1};

bool solve(int sx, int sy, int sz, int st) {
    using PIII = tuple<int, int, int, int>;
    queue<PIII> q;
    q.emplace(sz, sx, sy, 0);
    while (!q.empty()) {
        auto &[z, x, y, t] = q.front();
        q.pop();
        vis[z][x][y] = true;
        for (int i = 0; i < 4; i++) {
            int x0 = dx[i] + x, y0 = dy[i] + y;
            if (x0 >= n || x0 < 0 || y0 >= m || y0 < 0) continue;
            const auto c = map[z][x0][y0];
            if (vis[z][x0][y0] || c == '*') continue;
            cout << "c: " << c << " z: " << z << " x0: " << x0 << " y0: " << y0 << " t: " << t << endl;
            if (c == 'P') return t + 1 > st;
            if (c == '#') {
                const auto &c2 = map[z ^ 1][x0][y0];
                if (c2 == '#' || c2 == '*') continue;
                else if (c2 == 'P') return t + 1 > st;
                else q.emplace(z ^ 1, x0, y0, t + 1);
            } else {
                q.emplace(z, x0, y0, t + 1);
            }
        }
    }
    return false;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int t;
        scanf("%d%d%d", &n, &m, &t);
        memset(vis, false, sizeof(vis));
        memset(map, 0, sizeof(map));
        for (int i = 0; i < 2; i++) {
            getchar();
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < m; k++) {
                    scanf("%c", &map[i][j][k]);
                    cout << map[i][j][k];
                    getchar();
                }
                cout << endl;
            }
        }
        if (solve(0, 0, 0, 0)) {
            printf("YES\n");
        } else puts("NO");
    }
    return 0;
}