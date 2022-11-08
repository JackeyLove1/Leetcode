#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>

using namespace std;

constexpr int N = 1e4 + 100;
int e[N], ne[N], h[N], idx;
int happy[N];
int f[N][2];
bool has[N];

inline void init() {
    memset(h, -1, sizeof h);
    idx = 0;
}

inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int n;

int dfs(int u) {
    f[u][1] = happy[u];
    for (int i = h[u]; i != -1; i = ne[i]) {
        int son = e[i];
        f[u][0] += dfs(son);
        f[u][1] += f[son][0];
    }
    return std::max(f[u][0], f[u][1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> happy[i];
    init();
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        add(b, a);
        has[a] = true;
    }

    int root = 1;
    while (has[root]) ++root;
    dfs(root);
    cout << max(f[root][0], f[root][1]) << endl;
    return 0;
}