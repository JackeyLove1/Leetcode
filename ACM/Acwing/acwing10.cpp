#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <cmath>
#include <cstdlib>

#pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

constexpr int N = 120;
int e[N], ne[N], h[N], idx;

inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int n, m;
int v[N], w[N];
int f[N][N];

inline void init() {
    memset(h, -1, sizeof h);
}

void dfs(int u) {
    for (int i = h[u]; i != -1; i = ne[i]) {
        int son = e[i];
        dfs(son);
        for (int j = m - v[u]; j >= 0; --j) {
            for (int k = 0; k <= j; ++k) {
                // 枚举子状态
                f[u][j] = max(f[u][j], f[u][j - k] + f[son][k]);
            }
        }
    }
    // 最后选上第u件物品
    for (int j = m; j >= v[u]; --j) f[u][j] = f[u][j - v[u]] + w[u];
    for (int j = 0; j < v[u]; ++j) f[u][j] = 0;
}

int main() {
    fhj();
    init();
    cin >> n >> m;
    int root = -1;
    int number = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> v[i] >> w[i] >> number;
        if (number == -1) root = i;
        else add(number, i);
    }
    dfs(root);
    cout << f[root][m] << endl;
    return 0;
}