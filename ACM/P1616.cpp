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

constexpr int N = 1e7 + 100;
using ll = long long;
int n, m;
// int v[N], w[N];
ll f[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> m >> n;
    int v, w;
    for (int i = 1; i <= n; ++i) {
        cin >> v >> w;
        for (int j = v; j <= m; ++j) {
            f[j] = max(f[j - v] + w, f[j]);
        }
    }
    cout << f[m] << endl;
    return 0;
}