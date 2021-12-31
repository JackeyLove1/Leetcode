#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
#include <set>
#include <list>
#include <unordered_map>
#include <unordered_set>

using namespace std;

const int N = 150;
int n, m;
int v[N], w[N], s[N];
int f[N][N];

struct good {
    int v, w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    vector<good> goods;
    for (int i = 1; i <= n; i++) {
        cin >> v[i] >> w[i] >> s[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= s[i] && k * v[i] <= j; k++) {
                f[i][j] = max(f[i][j], f[i - 1][j - k * v[i]] + k * w[i]);
            }
        }
    }
    cout << f[n][m] << endl;
    return 0;
}