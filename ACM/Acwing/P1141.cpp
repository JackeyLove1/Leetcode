#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <map>
#include <bitset>
#include <cstring>


using namespace std;

constexpr int N = 1e3 + 100, M = 1e6 + 100;
int n, m;
char g[N][N];
using PII = pair<int, int>;
int f[N][N], ans[M];

const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

void dfs(int x, int y, int z, int cur) {
    if (f[x][y] != -1) return;
    if (x < 0 || x >= n || y < 0 || y >= n || g[x][y] - '0' != z) return;
    f[x][y] = cur, ans[cur]++;
    for (int i = 0; i < 4; ++i) {
        dfs(x + dx[i], y + dy[i], !z, cur);
    }
    // cout << "cur: " << ans[cur] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> g[i];
    }
    memset(f, -1, sizeof f);
    while (m--) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        dfs(x, y, g[x][y] - '0', m);
        cout << ans[f[x][y]] << endl;
    }
    return 0;
}