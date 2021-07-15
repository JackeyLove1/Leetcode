#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <cstring>
#include <unordered_set>

using namespace std;

int n, m;
const int N = 110;

int g[N][N], d[N][N];

using PII = pair<int, int>;

int bfs() {
    queue<PII> q;
    memset(d, -1, sizeof d);
    d[0][0] = 0;
    q.push({0, 0});

    int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

    while (!q.empty()) {
        auto t = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int x = dx[i] + t.first, y = dy[i] + t.second;
            if (x >= 0 && x < n && y >= 0 && y < m && d[x][y] == -1 && g[x][y] == 0) {
                d[x][y] = d[t.first][t.second] + 1;
                q.push({x, y});
            }
        }
    }
    return d[n - 1][m - 1];
}

int main() {
    cin >> n >> m;
    ios::sync_with_stdio(false);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> g[i][j];
        }
    }

    cout << bfs() << endl;
    return 0;
}