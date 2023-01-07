#include <bits/stdc++.h>

using namespace std;

constexpr int N = 5010, M = 100010, INF = 1e8;

int n, m, S, T;
int h[N], e[M], f[M], w[M], ne[M], idx;
int q[N], d[N], pre[N], incf[N];
bool st[N];

void add(int a, int b, int c, int d) {
    e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx++;
}

bool spfa() {
    int hh = 0, tt = 1;
    memset(d, -0x3f, sizeof d);
    memset(incf, 0, sizeof incf);
    q[0] = S, d[S] = 0, incf[S] = INF;
    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; ~i; i = ne[i]) {
            int ver = e[i];
            if (f[i] && d[ver] < d[t] + w[i]) {
                d[ver] = d[t] + w[i];
                pre[ver] = i;
                incf[ver] = min(f[i], incf[t]);
                if (!st[ver]) {
                    q[tt++] = ver;
                    if (tt == N) tt = 0;
                    st[ver] = true;
                }
            }
        }
    }

    return incf[T] > 0;
}

void EK(int &flow, int &cost) {
    flow = cost = 0;
    while (spfa()) {
        int t = incf[T];
        flow += t, cost += t * d[T];
        for (int i = T; i != S; i = e[pre[i] ^ 1]) {
            f[pre[i]] -= t;
            f[pre[i] ^ 1] += t;
        }
    }
}

inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}  // 快读

inline int get(int x, int y) {
    return x * (m + 1) + y;
}

int main() {
    memset(h, -1, sizeof h);
    int A = read(), B = read();
    n = read(), m = read();
    S = (n + 1) * (m + 1) + 1, T = S + 1;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < m; ++j) {
            int c = read();
            add(get(i, j), get(i, j + 1), 1, c);
            add(get(i, j), get(i, j + 1), INF, 0);
        }
    }
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j < n; ++j) {
            int c = read();
            add(get(j, i), get(j + 1, i), 1, c);
            add(get(j, i), get(j + 1, i), INF, 0);
        }
    }
    while (A--) {
        int k = read(), x = read(), y = read();
        add(S, get(x, y), k, 0);
    }
    while (B--) {
        int r = read(), x = read(), y = read();
        add(get(x, y), T, r, 0);
    }
    int flow, cost;
    EK(flow, cost);
    cout << cost << endl;
    return 0;
}