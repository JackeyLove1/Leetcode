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
constexpr int N = 50010, M = (N + 125003) * 2, INF = numeric_limits<int32_t>::max();
int n, m, S, T;

// d is level, cur is current curve
int h[N], e[M], f[M], ne[M], l[M], idx;
int d[N], cur[N];
int A[N];

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
    int s, t;
    cin >> n >> m >> s >> t;
    memset(h, -1, sizeof h);
    S = 0, T = n + 1; // set super source target
    int a, b, c, d;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> c >> d;
        add(a, b, d - c);
        A[a] -= c, A[b] += c;
    }
    int s_flow = 0;
    for (int i = 1; i <= n; ++i) {
        if (A[i] > 0) add(S, i, A[i]), s_flow += A[i];
        else add(i, T, -A[i]);
    }
    add(t, s, INF);
    auto max_flow = dinic();
    if (s_flow != max_flow) {
        cout << "No Solution" << endl;
        return 0;
    } else {
        int res1 = f[idx - 1];
        S = s, T = t;
        f[idx - 1] = f[idx - 2] = 0;
        cout << res1 + dinic() << endl;
    }
    return 0;
}