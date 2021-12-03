#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <unordered_map>
#include <bitset>

using namespace std;

constexpr int N = 1e3 + 10;
int nums[N];
int f[N][N];
int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> nums[i];
        nums[i + n] = nums[i];
    }

    for (int len = 3; len <= n + 1; ++len) {
        for (int i = 1; i + len - 1 <= n * 2; ++i) {
            int j = i + len - 1;
            for (int k = i + 1; k < j; ++k) {
                f[i][j] = max(f[i][j], f[i][k] + nums[i] * nums[k] * nums[j] + f[k][j]);
            }
        }
    }

    int maxn = -1e9;
    for (int i = 1; i <= n; ++i) {
        maxn = max(maxn, f[i][i + n]);
        // cout << maxn << endl;
    }
    cout << maxn << endl;
    return 0;
}