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
// #include <array>
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

constexpr int N = 1100, M = 65, INF = 0x3f3f3f3f, MOD = 1e4;
char g[N][N];
bool st[N][N];
int n, m;
// left right up down
constexpr int dx[]{-1, 1, 0, 0}, dy[]{0, 0, -1, 1};

struct node {
    int x, y, times;

    explicit node(int x_, int y_, int times_) : x(x_), y(y_), times(times_) {}

    bool operator<(const node &rhs) const {
        return times < rhs.times;
    }
};

inline int solve() {
    while (cin >> n >> m && n && m) {
        priority_queue<node> q;
        memset(g, 0, sizeof g);
        memset(st, false, sizeof st);
        int x0, y0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> g[i][j];
                if (g[i][j] == 'S') x0 = i, y0 = j;
            }
        }
        q.emplace(x0, y0, 0);
        while (!q.empty()) {
            auto tx = q.top().x, ty = q.top().y, tt = q.top().times;
            q.pop();
            st[tx][ty] = true;
            for (int i = 0; i < 4; ++i) {
                auto x3 = tx + dx[i], y3 = ty + dy[i];
                if (x3 < 0 || x3 >= n || y3 < 0 || y3 >= m) continue;
                if (g[x3][y3] == '*' || st[x3][y3]) continue;
                if (g[x3][y3] == '.') {
                    q.emplace(x3, y3, tt + 1);
                    continue;
                }
                if (g[x3][y3] == 'T') {
                    return tt + 1;
                }
                if ((i == 0 || i == 1) && g[x3][y3] == '-') {
                    if (tt % 2) q.emplace(x3, y3, tt + 2);
                    else q.emplace(x3, y3, tt + 1);
                    continue;
                }
                if ((i == 2 || i == 3) && g[x3][y3] == '|') {
                    if (tt % 2)q.emplace(x3, y3, tt + 1);
                    else q.emplace(x3, y3, tt + 2);
                }
            }
        }
    }
    return -1;
}

int main() {
    fhj();
    cout << solve() << endl;
    return 0;
}