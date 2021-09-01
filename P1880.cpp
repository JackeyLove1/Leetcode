#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <climits>
#include <functional>

using namespace std;

int n;
constexpr int N = 300;
int nums[N];
int s[N];
int f[N][N], g[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
        nums[i + n] = nums[i];
    }
    memset(f, 0x3f, sizeof f);
    memset(g, -0x3f, sizeof g);
    for (int i = 1; i <= 2 * n; i++) {
        s[i] = s[i - 1] + nums[i];
    }
    for (int len = 1; len <= n; len++) {
        for (int l = 1, r; r = l + len - 1, r <= 2 * n; l++) {
            if (len == 1) f[l][l] = g[l][l] = 0;
            else {
                for (int k = l; k < r; k++) {
                    f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r] + s[r] - s[l - 1]);
                    g[l][r] = max(g[l][r], g[l][k] + g[k + 1][r] + s[r] - s[l - 1]);
                }
            }
        }
    }

    int maxn = INT_MIN, minn = INT_MAX;
    for (int i = 1; i <= n; i++) {
        maxn = max(maxn, g[i][i + n - 1]);
        minn = min(minn, f[i][i + n - 1]);
    }
    cout << minn << endl << maxn << endl;
    return 0;
}