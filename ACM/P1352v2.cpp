#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>

using namespace std;

constexpr int N = 1e4 + 100, M = 6e3 + 100;

int n, m;
int e[N], ne[N], h[N], idx;
int f[M][2];
int nums[M];
bool has[M];

inline void init() {
    memset(h, -1, sizeof h);
    idx = 0;
}

inline void add(int a, int b) { // a -> b
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u) {
    f[u][1] = nums[u];
    f[u][0] = 0;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int son = e[i];
        dfs(son); // from bottom to top dp
        f[u][1] += f[son][0];
        f[u][0] += max(f[son][1], f[son][0]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    init();
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
    }
    int l, k;
    for (int i = 0; i < n - 1; i++) {
        cin >> l >> k;
        add(k, l);
        has[l] = true;
    }
    int root = 1;
    while (has[root]) ++root;
    dfs(root);
    cout << max(f[root][1], f[root][0]) << endl;
    return 0;
}