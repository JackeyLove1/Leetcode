#include <bits/stdc++.h>

using namespace std;

const int N = 50100, M = 1000100, INF = 1e8;

int n, m, S, T;
int h[N], e[M], f[M], w[M], ne[M], idx;
int q[N], d[N], pre[N], incf[N];
bool st[N];

inline void add(int a, int b, int c, int d) {
    e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx++;
}

bool spfa() {
    int hh = 0, tt = 1;
    memset(d, 0x3f, sizeof d);
    memset(incf, 0, sizeof incf);
    q[0] = S, d[S] = 0, incf[S] = INF;
    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; ~i; i = ne[i]) {
            int ver = e[i];
            if (f[i] && d[ver] > d[t] + w[i]) {
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

#define K 220

int main() {
    memset(h, -1, sizeof h);
    n = read();
    S = 0, T = n + K + K + 1;
    for (int i = 1; i <= n; ++i) {
        int mi = read(), ai = read(), bi = read(), ki = read();
        for (int j = ai; j <= bi; ++j) {
            int cost = std::abs(mi - j) * ki;
            add(i, j + n, 1, cost);
        }
    }
    for (int i = 1; i <= n; ++i) add(S, i, 1, 0);
    for (int i = 1; i < K; ++i) add(i + n, i + n + K, 1, 0);
    for (int i = 1; i < K; ++i) add(i + n + K, T, 1, 0);
    int flow, cost;
    EK(flow, cost);
    if (flow < n) {
        cout << "NIE" << endl;
    } else {
        cout << cost << endl;
    }
    return 0;
}