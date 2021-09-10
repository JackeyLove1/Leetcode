#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <unordered_map>
#include <bitset>
#include <cstring>
#include <queue>

using namespace std;

int n;
constexpr int N = 1e3 + 10;
int nums[N][N];
int f[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            cin >> nums[i][j];
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            f[i][j] = max(f[i - 1][j], f[i - 1][j - 1]) + nums[i][j];
            // cout << "i: " << i << " j: " << j << " res: " << f[i][j] << endl;
        }
    }

    int maxn = 0;
    for (int i = 1; i <= n; ++i) {
        maxn = max(f[n][i], maxn);
    }
    cout << maxn << endl;
    return 0;
}