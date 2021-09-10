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

int n;
constexpr int N = 1e3 + 10, INF = 0x3f3f3f3f;
int g[N][N];
int f[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    memset(f, 0x3f, sizeof f);
    memset(g, 0x3f, sizeof g);
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            cin >> g[i][j];
        }
    }
    f[1] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < i; j++) {
            f[i] = min(f[i], f[j] + g[j][i]);
        }
    }
    cout << f[n] << endl;
    return 0;
}