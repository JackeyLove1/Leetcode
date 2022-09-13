#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

constexpr int N = 200;

int n, m;
char g[N][N];
int dist[N][N];
int sx, sy;

inline int bfs(){
    using PII = pair<int, int>;
    memset(dist, -1, sizeof dist);
    int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};
    queue<PII> q;
    q.push({sx, sy});
    dist[sx][sy] = 0;
    while (!q.empty()){
        auto t = q.front();
        q.pop();
        for(int i = 0; i < 8; i++){
            int x = dx[i] + t.first, y = dy[i] + t.second;
            if(x >= n || x < 0 || y >= m || y < 0) continue;
            if(dist[x][y] != -1 || g[x][y] == '*' ) continue;
            dist[x][y] = dist[t.first][t.second] + 1;
            if(g[x][y] == 'H') return dist[x][y];
            q.push({x, y});
        }
    }
    return -1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> g[i][j];
            if(g[i][j] == 'K'){
                sx = i, sy = j;
            }
        }
    }

    cout << bfs() << endl;
    return 0;
}