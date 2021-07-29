#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

constexpr int N = 1e3 + 100;
int g[N][N];
bool st[N][N];
int n;

using PII = pair<int, int>;

PII pre[N][N];

inline void bfs(int sx, int sy) {
    int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
    queue<PII> q;
    memset(pre, -1, sizeof(pre));
    q.push({sx, sy});
    // st[sx][sy] = true;
    pre[sx][sy] = {0, 0};
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int x0 = dx[i] + p.first, y0 = dy[i] + p.second;
            if (x0 < 0 || x0 >= n || y0 < 0 || y0 >= n) continue;
            // if (st[x0][y0]) continue; // 遍历过
            if (pre[x0][y0].first != -1) continue; // 遍历过
            if (g[x0][y0]) continue; // 遇到墙
            q.push({x0, y0});
            // st[x0][y0] = true;
            pre[x0][y0] = p; // 记录前驱
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> g[i][j];
        }
    }

    bfs(n-1, n-1);
    PII end = {0, 0};
    while (end.first != n - 1 || end.second != n - 1) {
        cout << end.first << " "<< end.second << endl;
        end = pre[end.first][end.second];
    }
    cout << n-1 << " " << n-1 << endl;
    return 0;
}