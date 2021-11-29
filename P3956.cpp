#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;
constexpr int INF = 0x3f3f3f3f;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

struct node {
    int x, y, color, weight;

    explicit node(int x_, int y_, int color_, int weight_) :
            x(x_), y(y_), color(color_), weight(weight_) {}

    bool operator<(const node &rhs) const {
        return weight > rhs.weight;
    }
};

priority_queue<node> q;
constexpr int dx[] = {0, 1, 0, -1, 1, 1, -1, -1, 0, 2, 0, -2};//12方向及魔法代价
constexpr int dy[] = {1, 0, -1, 0, 1, -1, 1, -1, 2, 0, -2, 0};
constexpr int dw[] = {0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2};
constexpr int N = 110;
int color[N][N], dis[N][N];
int n, m;

void bfs() {
    memset(dis, 0x3f, sizeof dis);
    dis[1][1]= 0;
    q.push(node{1, 1, color[1][1], 0});
    while (!q.empty()) {
        auto cur = q.top();
        q.pop();
        auto[curx, cury, curc, curw] = cur;
        // 满足更新条件再更新
        if (dis[curx][cury] < curw) continue;
        for (int i = 0; i < 12; ++i) {
            auto next_x = curx + dx[i];
            auto next_y = cury + dy[i];
            auto next_w = curw + dw[i];
            // 检查坐标和颜色是否满足条件
            if (next_x <= 0 || next_x > m || next_y <= 0 || next_y > m) continue;
            auto next_c = color[next_x][next_y];
            if (!next_c) continue; // 无色格子跳过
            if (next_c != curc) next_w++; // 不同颜色计算步数
            if (next_w < dis[next_x][next_y]) {
                dis[next_x][next_y] = next_w;
                q.emplace(next_x, next_y, next_c, next_w);
            }
        }
    }
}

int main() {
    fhj();
    cin >> m >> n;
    int x, y, c;
    for (int i = 1; i <= n; ++i) {
        cin >> x >> y >> c;
        color[x][y] = c + 1;
    }
    bfs();
    if (!color[m][m]) {//处理(m,m)无色情况
        int ans = min(dis[m][m - 1], dis[m - 1][m]) + 2;
        if (ans >= INF)puts("-1");
        else printf("%d\n", ans);
    } else {
        if (dis[m][m] == INF)puts("-1");
        else printf("%d\n", dis[m][m]);
    }
    return 0;
}