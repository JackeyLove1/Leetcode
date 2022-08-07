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
constexpr int N = 210, M = (10200 + N) * 2, INF = 1e9;
int n, m, S, T;

// d is level, cur is current curve
int h[N], e[M], f[M], ne[M], l[M], idx;
int d[N], cur[N];
int A[N];

inline void add(int a, int b, int c, int d) {
    e[idx] = b, f[idx] = d - c, l[idx] = c, ne[idx] = h[a], h[a] = idx++; // positive
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
    cin >> n >> m;
    memset(h, -1, sizeof h);
    S = 0, T = n + 1; // set super source target
    int a, b, in, out;
    for(int i = 0; i < m; ++i) {
        cin >> a >> b >> in >> out;
        add(a, b, in, out);
        A[a] -= in, A[b] += in;
    }
    int all_flow = 0;
    for (int i = 1; i <= n; ++i) {
        if (A[i] > 0) add(S, i, 0, A[i]), all_flow += A[i];
        else add(i, T, 0, -A[i]);
    }
    auto res = dinic();
    if (res != all_flow) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        for (int i = 0; i < m * 2; i += 2) {
            cout << f[i ^ 1] + l[i] << endl;
        }
    }
    return 0;
}