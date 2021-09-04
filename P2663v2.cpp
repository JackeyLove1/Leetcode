#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <climits>
#include <functional>
#include <numeric>

using namespace std;

constexpr int N = 1e4 + 100, M = 105;
int n;
int nums[N];
bool f[M][M][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
        sum += nums[i];
    }
    for (int i = 0; i <= n; i++) f[i][0][0] = true;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            for (int k = 0; k <= sum; k++) {
                f[i][j][k] |= f[i - 1][j][k];
                if (k >= nums[i]) f[i][j][k] |= f[i - 1][j - 1][k - nums[i]];
            }
        }
    }
    sum /= 2;
    n /= 2;
    for (int i = sum; i >= 0; i--) {
        if (f[n * 2][n][i]) {
            cout << i << endl;
            break;
        }
    }
    return 0;
}