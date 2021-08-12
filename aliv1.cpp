#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <list>
#include <map>
#include <cmath>
#include <unordered_map>
#include <unordered_set>

using namespace std;
const int N = 10;
const int n = 3;
char g[N][N], tmp[N][N];

const int dx[] = {0, 0, 1, 0, -1}, dy[] = {0, 1, 0, -1, 0};

inline void turn(int x, int y) { // 改变x y位置的状态
    for (int i = 0; i < 5; i++) {
        int x0 = x + dx[i], y0 = y + dy[i];
        if (x0 >= n || x0 < 0 || y0 >= n || y0 < 0) continue;
        if (tmp[x0][y0] == 'U') tmp[x0][y0] = 'D';
        else tmp[x0][y0] = 'U';
    }
}

inline void print() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << tmp[i][j] << ' ';
        }
        cout << endl;
    }
}

inline int solve(int t) {
    int res = 0;
    for (int i = 0; i < n; i++) {
        if (t & (1 << i))
            turn(0, i), res++;
    }
    for (int i = 0; i < n; i++) {
        if (tmp[0][i] == 'U')
            turn(1, i), res++;
    }
    for (int i = 0; i < n; i++) {
        if (tmp[1][i] == 'U')
            turn(1, i), res++;
    }
    for (int i = 0; i < n; i++) {
        if (tmp[2][i] == 'U') return 1e9;
    }
    // cout << "t: " << t << " res: " << res << endl;
    // print();
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> g[i][j];
        }
    }
    int res = 1e9;
    for (int i = 0; i < 8; i++) { // 枚举第一行状态 2 ^ 3 = 8
        memcpy(tmp, g, sizeof g);
        res = min(res, solve(i));
    }
    if (res == 1e9) cout << -1 << endl; // 不存在路径
    else cout << res << endl; // 最小次数
    return 0;
}


