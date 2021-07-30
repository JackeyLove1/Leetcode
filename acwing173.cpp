#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

constexpr int N = 1200;

int n, m;
char g[N][N];
int dist[N][N];

inline int cal(int a, int b, int c, int d) {
    return abs(a - c) + abs(b - d);
}

inline void bfs() {
    using PII = pair<int, int>;
    memset(dist, -1, sizeof dist);
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};
    queue<PII> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == '1') {
                q.push({i, j});
                dist[i][j] = 0;
            }

        }
    }
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int x = dx[i] + t.first, y = dy[i] + t.second;
            if (x >= n || x < 0 || y >= m || y < 0) continue;
            if (dist[x][y] != -1) continue;
            dist[x][y] = dist[t.first][t.second] + 1;
            // cout << "x: "<<x << " y: " << y << " dist: " << dist[x][y] << endl;
            q.push({x, y});
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> g[i][j];
        }
    }
    bfs();
    return 0;
}