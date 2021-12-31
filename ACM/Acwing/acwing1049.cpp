#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

constexpr int N = 1e6;
int f[N], nums[N];
int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 2; i <= n + 1; i++) {
            cin >> nums[i];
        }

        for (int i = 2; i <= n + 1; i++) {
            f[i] = max(f[i - 1], f[i - 2] + nums[i]);
        }

        cout << f[n + 1] << endl;
    }
    return 0;
}