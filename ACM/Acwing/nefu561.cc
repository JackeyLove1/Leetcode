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
#include <tuple>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using PII = pair<int, int>;


static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 110, M = 65, INF = 0x3f3f3f3f, MOD = 1e4;
constexpr int dx[]{1, 0, -1, 0}, dy[]{0, 1, 0, -1};
constexpr int sz = sizeof dx / sizeof dx[0];
int n, m;
char g[N][N];
bool st[N][N];
int sx, sy;

inline bool check(int x, int y) {
    if (x >= n || x < 0 || y >= m || y < 0) return false;
    else if (g[x][y] == '#' || st[x][y]) return false;
    else return true;
}

void dfs(int x, int y, int& cnt) {
    st[x][y] = true;
    for (int i = 0; i < sz; ++i) {
        auto x0 = x + dx[i], y0 = y + dy[i];
        if (check(x0, y0)){
            ++cnt;
            dfs(x0, y0, cnt);
        }
    }
}

int main() {
    fhj();
    while (cin >> m >> n && n && m) {
        memset(st, false, sizeof st);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> g[i][j];
                if (g[i][j] == '@') {
                    sx = i, sy = j;
                }
            }
        }
        int cnt = 1;
        dfs(sx, sy, cnt);
        cout << cnt << endl;
    }
    return 0;
}