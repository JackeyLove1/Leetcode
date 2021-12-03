#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>

using namespace std;

constexpr int N = 1e5 + 100;
int nums[N];
int f[N][120][2];
int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    memset(f, -0x3f, sizeof f);
    f[0][0][0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
        for (int j = 0; j <= m; j++) {
            // f[i][j][2] = max(f[i - 1][j][0], f[i - 1][j][1]) + nums[i];
            f[i][j][0] = f[i - 1][j][0];
            if (j > 0) f[i][j][0] = max(f[i][j][0], f[i - 1][j - 1][1] + nums[i]);
            f[i][j][1] = max(f[i - 1][j][0] - nums[i], f[i - 1][j][1]);
        }
    }
    int res = 0;
    for (int j = 0; j <= m; j++) res = max(res, f[n][j][0]);
    cout << res << endl;
    return 0;
}