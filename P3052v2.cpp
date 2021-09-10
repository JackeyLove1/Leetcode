#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <unordered_map>
#include <bitset>
#include <cstring>

using namespace std;

constexpr int N = 3e5 + 100, M = 20, INF = 0x3f3f3f3f;

int n, m;
int w[M];
int up;
int f[M][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    up = 1 << n;
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
    }
    memset(f, 0x3f, sizeof f);
    for (int i = 0; i < n; ++i) {
        f[1][1 << i] = w[i]; // 初始化边界条件
    }
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < up; j++) {
            if (f[i][j] != INF) { // 表明该状态可转移
                // 枚举牛
                for (int k = 0; k < n; ++k) {
                    if (j & (1 << k)) continue; // 表明这头牛已经上车
                    if (f[i][j] + w[k] <= m) { // 装得下
                        // 进行状态转移
                        f[i][j | (1 << k)] = min(f[i][j | (1 << k)], f[i][j] + w[k]);
                    } else { // 装不下
                        f[i + 1][j | (1 << k)] = min(f[i][j | (1 << k)], w[k]);
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (f[i][up - 1] != INF) {
            cout << i << endl;
            return 0;
        }
    }
    return 0;
}