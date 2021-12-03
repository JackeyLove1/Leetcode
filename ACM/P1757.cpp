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
using PII = pair<int, int>;
vector<PII> s[N];
int f[N][N];
int n, m;

int main() {
    cin >> m >> n;
    int a, b, c;
    for (int i = 1; i <= n; ++i) {
        cin >> a >> b >> c;
        s[c].emplace_back(a, b);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; j++) {
            f[i][j] = f[i - 1][j];
            for (auto&&[v, w] : s[i]) {
                if (j >= v) f[i][j] = max(f[i][j], f[i - 1][j - v] + w);
            }
        }
    }
    cout << f[n][m] << endl;
    return 0;
}