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
constexpr int N = 210, M = 1e5 + 100, INF = numeric_limits<int32_t>::max();
int n, m, S, T;

// d is level, cur is current curve
int h[N], e[M], f[M], ne[M], idx, w[M];
int d[N], cur[N];

inline void add(int a, int b, int c) {
    e[idx] = b, f[idx] = 1, w[idx] = c, ne[idx] = h[a], h[a] = idx++; // positive
    e[idx] = a, f[idx] = 0, w[idx] = c, ne[idx] = h[b], h[b] = idx++; // negative
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

int k;

inline bool check(int mid) {
    for (int i = 0; i < idx; i++) {
        if (w[i] > mid) f[i] = 0;
        else f[i] = 1;
    }
    if (dinic() >= k) return true;
    return false;
}

int main() {
    fhj();
    cin >> n >> m >> k;
    memset(h, -1, sizeof h);
    S = 1, T = n;
    int a, b, c;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> c;
        add(a, b, c);
    }
    int l = 1, r = 1e6;
    while (l < r) {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << r << endl;
    return 0;
}