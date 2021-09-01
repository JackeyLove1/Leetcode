#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <climits>
#include <functional>

using namespace std;

constexpr int N = 50;
using ll = long long;
ll f[N][N];
int st[N][N];
int m, n, xh, yh;
constexpr int dx[] = {0, -2, -1, 1, 2, 2, 1, -1, -2};
constexpr int dy[] = {0, 1, 2, 2, 1, -1, -2, -2, -1};

int main() {
    ios::sync_with_stdio(false);
    cin >> m >> n >> xh >> yh;
    m++, n++, xh++, yh++;
    for (int i = 0; i < 9; i++) {
        int x0 = xh + dx[i], y0 = yh + dy[i];
        if (x0 <= m && x0 >= 1 && y0 <= n && y0 >= 1) {
            st[x0][y0] = 1;
        }
    }
    f[0][1] = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (st[i][j]) f[i][j] = 0;
            else f[i][j] = f[i - 1][j] + f[i][j - 1];
            // cout << "i: " << i << " j: " << j << " res: " << f[i][j] << endl;
        }
    }

    cout << f[m][n] << endl;
    return 0;
}