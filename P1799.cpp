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
int f[N][N], q[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> q[i];
    }
    int maxn = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (j > 0) f[i][j] = f[i - 1][j - 1];
            f[i][j] = max(f[i][j], f[i - 1][j] + (q[i] == i - j));
            maxn = max(maxn, f[i][j]);
        }
    }
    cout << maxn << endl;
    return 0;
}