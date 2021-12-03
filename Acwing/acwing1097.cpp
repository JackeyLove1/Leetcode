#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

constexpr int N = 1100;
int n, m;
char g[N][N];

constexpr int dx[] = {1, 0, -1, 0, 1, -1, 1, -1}, dy[] = {0, 1, 0, -1, 1, -1, -1, 1};
using PII = pair<int, int>;

inline void bfs(int x, int y) {
    queue<PII> q;
    q.push({x, y});
    while (!q.empty()) {
        auto[x0, y0] = q.front();
        g[x0][y0] = '.';
        q.pop();
        for (int i = 0; i < 8; i++) {
            int xn = x0 + dx[i], yn = y0 + dy[i];
            if (xn < 0 || yn < 0 || xn >= n || yn >= m) continue;
            if (g[xn][yn] == '.') continue;
            q.push({xn, yn});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    char ch;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> g[i][j];
        }
    }
    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == 'W' ) {
                bfs(i, j);
                res++;
            }
        }
    }
    cout << res << endl;
    return 0;
}