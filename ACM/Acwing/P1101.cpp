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
constexpr int N = 120;
int n;
const int dx[] = {1, 0, 1, -1, 0, -1, 1, -1};
const int dy[] = {0, 1, 1, 0, -1, -1, -1, 1};
int st[N][N];
const string s = "yizhong";
const int endPos = 7;
static int res = 0;
char g[N][N];

void dfs(int x, int y, int i, int cur) { // i is the direction
    if (cur == endPos) {
        ++res;
        // 从x和y开始沿着i方向的逆方向开始标记
        for (int k = 0; k < 7; ++k) {
            x = x - dx[i], y = y - dy[i];
            st[x][y] = 1;
        }
        return;
    }
    if (x < 0 || x >= n || y < 0 || y >= n) return;
    if (s[cur] != g[x][y]) return;
    int xn = x + dx[i], yn = y + dy[i];
    dfs(xn, yn, i, cur + 1);
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> g[i];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (g[i][j] == 'y') {
                for (int k = 0; k < 8; ++k) {
                    dfs(i, j, k, 0);
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (st[i][j]) cout << g[i][j];
            else cout << '*';
        }
        cout << endl;
    }
    // cout << res << endl;
    return 0;
}