#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#include <unordered_map>
#include <numeric>
#include <string>

using namespace std;

constexpr int MOD = 1e6 + 7, N = 1e3 + 100;
int f[N][N];
int nums[N];
int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
    }
    // 初始化
    // for (int i = 0; i <= n; i++) f[i][0] = 1;
    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= j && k <= nums[i]; k++) {
                f[i][j] = (f[i][j] + f[i - 1][j - k]) % MOD;
            }
        }
    }
    cout << f[n][m] << endl;
    return 0;
}