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
int n, m, x;
int a[N], b[N], c[N];
ll f[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> x;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i] >> b[i] >> c[i];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = m; j >= b[i]; j--) {
            for (int k = x; k >= c[i]; k--) {
                f[j][k] = max(f[j][k], f[j - b[i]][k - c[i]] + a[i]);
            }
        }
    }
    cout << f[m][x] << endl;
    return 0;
}