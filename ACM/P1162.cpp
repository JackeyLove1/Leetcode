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

constexpr int N = 50;
int a[N][N], b[N][N];
bool st[N][N];
int n;
const int dx[] = {0, -1, 0, 1}, dy[] = {1, 0, -1, 0};

void dfs(int x, int y) {
    if (x < 0 || x > n + 1 || y < 0 || y > n + 1) return;
    if (a[x][y]) return;
    a[x][y] = 1;
    for (int i = 0; i < 4; ++i) {
        dfs(x + dx[i], y + dy[i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> b[i][j];
            if (b[i][j] == 0) a[i][j] = 0;
            else a[i][j] = 1;
        }
    }
    memset(st, 0, sizeof st);
    dfs(0, 0);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (a[i][j] == 0) cout << 2 << " ";
            else cout << b[i][j] << " ";
        }
        cout << endl;
    }
}