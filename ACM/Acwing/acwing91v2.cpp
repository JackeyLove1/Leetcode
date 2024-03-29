#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <list>
#include <unordered_map>
#include <unordered_set>

using namespace std;

constexpr int N = 22;
int f[1 << 20][N], d[N][N];
int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> d[i][j];
        }
    }
    memset(f, 0x3f, sizeof f);
    f[1][0] = 0;
    for (int i = 0; i < 1 << n; i++) {
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                for (int k = 0; k < n; k++) {
                    if ((i >> k) & 1) {
                        f[i][j] = min(f[i][j], f[i - (1 << j)][k] + d[k][j]);
                    }
                }
            }
        }
    }
    cout << f[(1 << n) - 1][n - 1] << endl;
    return 0;
}