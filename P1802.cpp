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
using ll = long long;
int n, m;
ll f[N][N], q[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    int w1, w2, v;
    for (int i = 1; i <= n; ++i) {
        cin >> w1 >> w2 >> v;
        for (int j = m; j >= 0; j--) {
            f[i][j] = max(f[i][j], f[i - 1][j] + w1);
            if (j >= v) f[i][j] = max(f[i][j], f[i - 1][j - v] + w2);
        }
    }
    cout << 5 * f[n][m] << endl;
    return 0;
}