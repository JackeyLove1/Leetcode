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
constexpr int dx[]{0, 0, 1, 1, 1, -1, -1, -1};
constexpr int dy[]{1, -1, 1, -1, 0, 0, 1, -1};
int n, m;
char g[N][N];
int dist[N][N];
bool vis[N][N];

inline bool check(int x, int y) {
    if (x >= n || x < 0 || y >= m || y < 0) return false;
    else if (vis[x][y] || g[x][y] == '*') return false;
    else return true;
}

inline void dfs(int x, int y) {
    vis[x][y] = true;
    for (int i = 0; i < 8; i++) {
        int x0 = dx[i] + x, y0 = dy[i] + y;
        if (check(x0, y0)) {
            dfs(x0, y0);
        }
    }
}

inline void solve() {
    while (cin >> n >> m && m && n) {
        memset(vis, false, sizeof vis);
        queue<PII> q;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> g[i][j];
            }
        }
        int res = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (g[i][j] == '@' && !vis[i][j]) {
                    ++res;
                    dfs(i, j);
                }
            }
        }
        cout << res << endl;
    }
}

int main() {
    fhj();
    solve();
    return 0;
}