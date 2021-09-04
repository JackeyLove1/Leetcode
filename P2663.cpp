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
bool f[M][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
        sum += nums[i];
    }
    f[0][0] = true;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j >= 1; j--) {
            for (int k = sum; k >= nums[i]; k--) {
                f[j][k] |= f[j - 1][k - nums[i]];
            }
        }
    }
    sum /= 2;
    n /= 2;
    for (int i = sum; i >= 0; i--) {
        if (f[n][i]) {
            cout << i << endl;
            break;
        }
    }
    return 0;
}