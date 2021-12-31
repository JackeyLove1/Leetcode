#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>

using namespace std;

constexpr int N = 1e5 + 100;
int nums[N];
int f[N][3];
int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> nums[i];
    // init
    memset(f, -0x3f, sizeof f);
    f[0][0] = 0, f[0][2] = 0;
    // transfer states
    for (int i = 1; i <= n; i++) {
        f[i][0] = max(f[i - 1][2], f[i - 1][0]);
        f[i][1] = max(f[i - 1][1], f[i - 1][0] - nums[i]);
        f[i][2] = f[i - 1][1] + nums[i];
    }

    cout << max(f[n][0], f[n][2]) << endl;
    return 0;
}