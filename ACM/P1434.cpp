#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>

using namespace std;
constexpr int N = 110;
int n, m;
int g[N][N];
int f[N][N];
bool st[N][N];
using PII = pair<int, int>;
map<PII, int> cache;

const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

int dfs(int x, int y) {
    PII p = {x, y};
    if (cache.count(p)) return cache[p];
    cache[p] = 1;
    int &v = cache[p];
    for (int i = 0; i < 4; ++i) {
        int xn = x + dx[i], yn = y + dy[i];
        if (xn < 1 || xn > n || yn < 1 || yn > m) continue;
        if (g[xn][yn] <= g[x][y]) continue;
        v = max(v, dfs(xn, yn) + 1);
    }
    return v;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> g[i][j];
        }
    }
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            res = max(res, dfs(i, j));
        }
    }
    cout << res << endl;
    return 0;
}