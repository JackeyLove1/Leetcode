#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>
#include <climits>

using namespace std;

constexpr int N = 16010, M = 4e4;

int n;
int e[M], ne[M], h[M], idx;
int f[N];
int nums[N];

inline void init() {
    memset(f, -1, sizeof f);
    memset(h, -1, sizeof h);
    memset(e, 0, sizeof e);
    memset(ne, 0, sizeof ne);
    idx = 0;
}

inline void add(int a, int b) { // a -> b
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u, int fa) {
    if (f[u] != -1) return;
    f[u] = nums[u];
    for (int i = h[u]; i != -1; i = ne[i]) {
        int v = e[i];
        if (v != fa) {
            dfs(v, u);
            f[u] += max(0, f[v]);
        }
    }
    // cout << "u: " << u << " f[u]: " << f[u] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    init();
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
    }
    int a, b;
    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b;
        add(a, b);
        add(b, a);
        // has[b] = true;
    }
    dfs(1, 0);
    int res = INT_MIN;
    for (int i = 1; i <= n; i++) {
        res = max(res, f[i]);
    }
    cout << res << endl;
    return 0;
}