// 二维前缀和模版题

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

constexpr int N = 1e3 + 100;

int q[N][N], s[N][N];

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> q[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            s[i][j] = q[i][j] + s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
        }
    }

    int x1, y1, x2, y2;
    while (k--) {
        cin >> x1 >> y1 >> x2 >> y2;
        cout << s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1 - 1][y1 - 1] << endl;
    }

    return 0;
}