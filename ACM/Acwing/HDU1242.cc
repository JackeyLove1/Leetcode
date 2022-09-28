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

using namespace std;

using ll = long long;
using ull = unsigned long long;
using PII = pair<int, int>;


static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 310, M = 65, INF = 0x3f3f3f3f, MOD = 1e4;
char g[N][N];
bool st[N][N];
int n, m;
// left right up down
constexpr int dx[]{-1, 0, 1, 0}, dy[]{0, -1, 0, 1};

struct node {
    int x, y, times;

    explicit node(int x_, int y_, int times_) : x(x_), y(y_), times(times_) {}

    bool operator<(const node &rhs) const {
        return times > rhs.times;
    }
};

inline int solve() {
    cin >> n >> m;
    priority_queue<node> q;
    memset(g, 0, sizeof g);
    memset(st, false, sizeof st);
    int sx, sy;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> g[i][j];
            if (g[i][j] == 'a') sx = i, sy = j;
            // if (g[i][j] == 'r') ex = i, ey = j;
        }
    }
    q.emplace(sx, sy, 0);
    while (!q.empty()) {
        auto qx = q.top().x, qy = q.top().y, tt = q.top().times;
        // cout <<"qx: " << qx <<" qy: " << qy <<" tt: " << tt << endl;
        q.pop();
        st[qx][qy] = true;
        for (int i = 0; i < 4; ++i) {
            auto tx = qx + dx[i], ty = qy + dy[i];
            if (tx < 0 || tx >= n || ty < 0 || ty >= m) continue;
            if (g[tx][ty] == '#' || st[tx][ty]) continue;
            if (g[tx][ty] == 'r') return tt + 1;
            if (g[tx][ty] == '.') {
                q.emplace(tx, ty, tt + 1);
                continue;
            }
            if (g[tx][ty] == 'x') {
                q.emplace(tx, ty, tt + 2);
            }
        }
    }
    return -1;
}

int main() {
    fhj();
    auto ans = solve();
    if(ans==-1){
        printf("Poor ANGEL has to stay in the prison all his life.\n");
    }
    else{
        printf("%d\n",ans);
    }
    return 0;
}