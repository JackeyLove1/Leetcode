#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <unordered_map>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>

using namespace std;

constexpr int N = 1e3 + 100;
using ll = long long;
int n, m, k, r;
ll f[N];
int q[N], v[N], w[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> k >> r;
    for (int i = 1; i <= n; ++i) {
        cin >> q[i];
    }
    for (int i = 1; i <= m; ++i) {
        cin >> v[i];
    }
    for (int i = 1; i <= m; ++i) {
        cin >> w[i];
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = r; j >= v[i]; j--) {
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    }
    int left = 0;
    for (int i = 1; i <= r; ++i) {
        if (f[i] >= k) {
            left = r - i;
            break;
        }
    }
    sort(q + 1, q + n);
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (left >= q[i]) {
            ++ans;
            left -= q[i];
        }
    }
    cout << ans << endl;
    return 0;
}