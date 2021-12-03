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

constexpr int N = 110;
int st[N][N];
char g[N][N];
static int res = 0;
int n, m;

const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

void dfs(int x, int y) {
    st[x][y] = 1;
    for (int i = 0; i < 4; ++i) {
        int xn = x + dx[i], yn = y + dy[i];
        if (xn < 0 || xn >= n || yn < 0 || yn >= m) continue;
        if (g[xn][yn] == '0' || st[xn][yn]) continue;
        dfs(xn, yn);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> g[i];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (g[i][j] != '0' && !st[i][j]) {
                dfs(i, j);
                ++res;
            }
        }
    }
    cout << res << endl;
    return 0;
}