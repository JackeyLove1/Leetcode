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
    memset(st, 0, sizeof(st));
    q.push({sx, sy});
    st[sx][sy] = true;
    pre[sx][sy] = {0, 0};
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            auto x = dx[i] + t.first, y = dy[i] + t.second;
            if (x >= n || y >= n || x < 0 || y < 0) continue;
            if (st[x][y] || g[x][y]) continue;
            q.push({x, y});
            st[x][y] = true;
            pre[x][y] = t;
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

    bfs(n - 1, n - 1);
    PII end = {0, 0};
    while (true) {
        cout << end.first << ' ' << end.second << endl;
        if (end.first == n - 1 && end.second == n - 1) break;
        end = pre[end.first][end.second];
    }
    return 0;
}