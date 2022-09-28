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

using namespace std;

using ll = long long;
using ull = unsigned long long;
using PII = pair<int, int>;


static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1001, M = 65, INF = 0x3f3f3f3f, MOD = 1e4;
int g[N][N];
bool st[N][N];
int n, m;
constexpr int dx[]{-1, 0, 1, 0}, dy[]{0, -1, 0, 1};

inline void solve() {
    while (cin >> n >> m && n && m) {
        memset(g, 0, sizeof g);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> g[i][j];
            }
        }
        int t;
        cin >> t;
        while (t--) {
            queue<PII> q;
            memset(st, false, sizeof st);
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            --x1, --y1, --x2, --y2;
            if (g[x1][y1] != g[x2][y2]) {
                cout << "NO" << endl;
                continue;
            }
            if (g[x1][y1] == 0 || g[x2][y2] == 0){
                cout << "NO" << endl;
                continue;
            }
            q.push({x1, y1});
            auto found = false;
            while (!q.empty() && !found) {
                auto x0 = q.front().first, y0 = q.front().second;
                q.pop();
                st[x0][y0] = true;
                for (int i = 0; i < 4 && !found; ++i) {
                    auto x3 = x0 + dx[i], y3 = y0 + dy[i];
                    if (x3 < 0 || x3 >= n || y3 < 0 || y3 >= m) continue;
                    // cout << "x3: " << x3 << " y3: " << y3 << endl;
                    if (x3 == x2 && y3 == y2) found = true;
                    if (g[x3][y3] || st[x3][y3]) continue;
                    q.push({x3, y3});
                }
            }
            if (found) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    }
}

int main() {
    fhj();
    solve();
    return 0;
}