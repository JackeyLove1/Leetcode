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
int n, m, t;
int times[N], costs[N];
ll f[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> t;
    for (int i = 1; i <= n; ++i) {
        cin >> times[i] >> costs[i];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = m; j >= costs[i]; j--) {
            for (int k = t; k >= times[i]; k--) {
                f[j][k] = max(f[j][k], f[j - costs[i]][k - times[i]] + 1);
            }
        }
    }
    cout << f[m][t] << endl;
    return 0;
}