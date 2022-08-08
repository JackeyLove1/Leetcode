#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <unordered_map>
#include <unordered_set>


using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;
constexpr int N = 1e5 + 1000;
int e[N], h[N], ne[N], w[N], idx = 0;

inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int dfs(int u, int color) {
    int res = 0;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        int tmp = dfs(j, w[j]);
        res += tmp + (color != w[j]);
        // cout << "u: " << u << " w[u]: " << w[u] << endl;
        // cout << " j: " << j << " w[j]: " << w[j] << " tmp: " << tmp << " res: " << res << endl;
    }
    return res;
}

int main() {
    fhj();
    memset(h, -1, sizeof h);
    int n;
    int x;
    cin >> n;
    for (int i = 2; i <= n; ++i) {
        cin >> x;
        add(x, i);
    }
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
    }
    int res = dfs(1, w[1]) + 1;
    cout << res << endl;
    return 0;
}