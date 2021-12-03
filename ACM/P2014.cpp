#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>

using namespace std;

constexpr int N = 1e6 + 100;

int n, m;
int e[N], ne[N], h[N], idx;
int f[330][330];
int nums[330];

inline void init() {
    memset(h, -1, sizeof h);
    idx = 0;
}

inline void add(int a, int b) { // a -> b
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u, int t) {
    if (t <= 0) return;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int v = e[i];
        for (int k = 0; k < t; k++) {
            f[v][k] = f[u][k] + nums[v];
        }
        dfs(v, t - 1);
        for (int k = 1; k <= t; k++) {
            f[u][k] = max(f[u][k], f[v][k - 1]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    init();
    int s, k;
    for (int i = 1; i <= n; i++) {
        cin >> k >> s;
        add(k, i);
        nums[i] = s;
    }

    dfs(0, m);
    cout << f[0][m] << endl;
    return 0;
}