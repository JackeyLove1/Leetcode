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

constexpr int N = 8;
int n, m, t;
int sx, sy, ex, ey;
int block[N][N], st[N][N];
const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
static int res = 0;

void dfs(int x, int y) {
    // cout << "xn: " << x << " yn: " << y << endl;
    if (x == ex && y == ey) {
        ++res;
        return;
    }
    for (int i = 0; i < 4; ++i) {
        int xn = x + dx[i], yn = y + dy[i];
        if (xn > n || xn < 1 || yn > m || yn < 1) continue;
        if (st[xn][yn] || block[xn][yn]) continue;
        st[x][y] = 1;
        dfs(xn, yn);
        st[x][y] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> t;
    cin >> sx >> sy >> ex >> ey;
    for (int i = 1; i <= t; ++i) {
        int x, y;
        cin >> x >> y;
        block[x][y] = 1;
    }
    dfs(sx, sy);
    cout << res << endl;
    return 0;
}