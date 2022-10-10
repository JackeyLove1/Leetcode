#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
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
constexpr int N = 10010, M = 200010, INF = 1e9;
int n, m, S, T;

// 使用超级源点和终点即可
// d is level, cur is current curve
int h[N], e[M], f[M], ne[M], idx;
int d[N], cur[N];

inline void add(int a, int b, int c) {
    e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx++; // positive
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx++; // negative
}

inline bool bfs() {
    queue<int> q;
    memset(d, -1, sizeof d);
    q.push(S), d[S] = 0, cur[S] = h[S];
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        for (int i = h[t]; ~i; i = ne[i]) {
            int ver = e[i];
            if (d[ver] == -1 && f[i]) {
                d[ver] = d[t] + 1;
                cur[ver] = h[ver];
                if (ver == T) return true;
                q.push(ver);
            }
        }
    }
    return false;
}

inline int find(int u, int limit) {
    if (u == T) return limit;
    int flow = 0;
    for (int i = cur[u]; ~i && flow < limit; i = ne[i]) {
        cur[u] = i;
        int ver = e[i];
        if (d[ver] == d[u] + 1 && f[i]) {
            int t = find(ver, min(f[i], limit - flow));
            if (!t) d[ver] = -1;
            f[i] -= t, f[i ^ 1] += t, flow += t;
        }
    }
    return flow;
}

int dinic() {
    int r = 0, flow;
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r;
}

int main() {
    fhj();
    cin >> m >> n;
    memset(h, -1, sizeof h);
    S = 0, T = n + 1; // set super source target
    for (int i = 1; i <= m; ++i) {
        add(S, i, 1);
    }
    for (int i = m + 1; i <= n; ++i) {
        add(i, T, 1);
    }
    int a, b;
    while (cin >> a >> b && a != -1 && b != -1) {
        add(a, b, 1);
    }
    cout << dinic() << endl;
    for (int i = 0; i < idx; i += 2) {
        if (e[i] > m && e[i] <= n && !f[i]) {
            cout << e[i ^ 1] << " " << e[i] << endl;
        }
    }
    return 0;
}