#pragma GCC optimize(2)
#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 20, INF = 1e9 + 100;
using ll = long long;
int n, m;
constexpr int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
int op[N][N], g[N][N], tmp[N][N];

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> g[i][j];
        }
    }
    auto check = [&](int x, int y) -> bool {
        return x >= 0 && x < n && y >= 0 && y < m;
    };
    auto flip = [&](int x, int y) -> void {
        tmp[x][y] ^= 1;
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if (check(nx, ny)) tmp[nx][ny] ^= 1;
        }
    };
    auto flag = true;
    for (int i = 0; i < (1 << m); i++) {//字典序遍历第一行的翻转
        flag = true;
        memcpy(tmp, g, sizeof g);
        memset(op, 0, sizeof op);
        for (int j = 0; j < m; j++)
            if (i >> j & 1) flip(0, j), op[0][j] = 1;

        for (int j = 0; j < n - 1; j++)
            for (int k = 0; k < m; k++) if (tmp[j][k]) flip(j + 1, k), op[j + 1][k] = 1;
        for (int j = 0; j < m; j++) if (tmp[n - 1][j]) flag = false;//全0表示答案可行
        if (flag) break;
    }
    if (flag) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) cout << op[i][j] << " ";
            cout << endl;
        }
    } else {
        cout << "IMPOSSIBLE" << endl;
    }
    return 0;
}