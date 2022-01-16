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

constexpr int N = 1e3 + 100;
char g[N][N];
const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
int n, m;
static int res = 0;
static string str = "hehe";

void dfs(int x, int y, int dir, int cur) {
    if (cur == 4) {
        ++res;
        return;
    }
    if (g[x][y] != str[cur]) return;
    int xn = x + dx[dir], yn = y + dy[dir];
    if (xn < 0 || xn >= n || yn < 0 || yn >= m) return;
    dfs(xn, yn, dir, cur + 1);
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> g[i];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (g[i][j] == 'h') {
                for (int dir = 0; dir < 4; ++dir) {
                    dfs(i, j, dir, 0);
                }
            }
        }
    }
    cout << res << endl;
    return 0;
}