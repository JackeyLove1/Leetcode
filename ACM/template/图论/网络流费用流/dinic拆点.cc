#include <bits/stdc++.h>

using namespace std;

const int N = 410, M = 40610, INF = 1e8;

int n, F, D, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];

void add(int a, int b, int c) {
    e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}

bool bfs() {
    int hh = 0, tt = 0;
    memset(d, -1, sizeof d);
    q[0] = S, d[S] = 0, cur[S] = h[S];
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int ver = e[i];
            if (d[ver] == -1 && f[i]) {
                d[ver] = d[t] + 1;
                cur[ver] = h[ver];
                if (ver == T) return true;
                q[++tt] = ver;
            }
        }
    }
    return false;
}

int find(int u, int limit) {
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

inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}  // 快读

inline int id(int p, int x) {
    switch (p) {
        case 1:
            return 2 * n + x; // food
        case 2:
            return 2 * n + F + x; // drink
        case 3:
            return n + x; // out
        case 4:
            return x; // in
    }
    return 0;
}

int main() {
    n = read(), F = read(), D = read();
    S = 0, T = n * 2 + F + D + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= F; i++) add(S, id(1, i), 1);
    for (int i = 1; i <= D; i++) add(id(2, i), T, 1);
    for (int i = 1; i <= n; i++) {
        add(id(4, i), id(3, i), 1);
        int a, b, t;
        a = read(), b = read();
        while (a--) {
            t = read();
            add(id(1, t), id(4, i), 1);
        }
        while (b--) {
            t = read();
            add(id(3, i), id(2, t), 1);
        }
    }
    cout << dinic() << endl;
    return 0;
}