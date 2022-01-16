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

constexpr int N = 1e3 + 100;
int n;
int nums[N], s[N];
int f[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> nums[i];
        s[i] = nums[i] + s[i - 1];
    }
    if (s[n] < 0) {
        cout << "Impossible" << endl;
        return 0;
    }
    for (int i = 1; i <= n; ++i) {
        if (s[i] >= 0) {
            for (int j = 0; j < i; ++j) {
                if (s[i] - s[j] >= 0) {
                    f[i] = max(f[i], f[j] + 1);
                }
            }
        }
    }
    cout << f[n] << endl;
    return 0;
}