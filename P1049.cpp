#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <climits>
#include <functional>

using namespace std;

int n, m;
constexpr int N = 2e4 + 100;
int f[N];
int nums[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> m >> n;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
        for (int j = m; j >= nums[i]; j--) {
            f[j] = max(f[j], f[j - nums[i]] + nums[i]);
        }
    }
    cout << m - f[m] << endl;
    return 0;

}