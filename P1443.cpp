#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <map>
#include <bitset>
#include <cstring>
#include <queue>

using namespace std;

constexpr int N = 500;
int n, m, x, y;
// char g[N][N];
const int dx[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
const int dy[8] = {2, 1, -1, -2, 2, 1, -1, -2};
using PII = pair<int, int>;
// bool st[N][N];
int dist[N][N];

inline void bfs() {
    queue<PII> q;
    q.push({x, y});
    dist[x][y] = 0;
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        int x0 = t.first, y0 = t.second;
        for (int i = 0; i < 8; ++i) {
            int xn = x0 + dx[i], yn = y0 + dy[i];
            if (xn >= n || xn < 0 || yn >= m || yn < 0) continue;
            if (dist[xn][yn] != -1) continue;
            dist[xn][yn] = dist[x0][y0] + 1;
            q.push({xn, yn});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> x >> y;
    memset(dist, -1, sizeof dist);
    --x, --y;
    bfs();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%-5d",dist[i][j]);
        }
        cout << endl;
    }
    return 0;
}