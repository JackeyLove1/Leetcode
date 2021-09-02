#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <climits>
#include <functional>

using namespace std;
constexpr int N = 1e5;

int n, m;
int nums[N], f[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
        for (int j = m; j >= nums[i]; j--) {
            f[j] += f[j - nums[i]];
        }
    }
    cout << f[m] << endl;
    return 0;
}