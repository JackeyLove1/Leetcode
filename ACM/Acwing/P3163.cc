#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ll = long long;

constexpr int N = 100100, M = 200010, INF = 1e9 + 100;

// cur为当前弧
// d为层次图的层次
int n, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
ll q[N], d[N], cur[N];

inline void init() {
    idx = 0;
    memset(h, -1, sizeof h);
    memset(e, 0, sizeof e);
    memset(f, 0, sizeof f);
    memset(ne, 0, sizeof ne);
    memset(q, 0, sizeof q);
    memset(d, 0, sizeof d);
    memset(cur, 0, sizeof cur);
}

inline void add(int a, int b, int c) {
    e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx++; // 正向边
    e[idx] = a, f[idx] = c, ne[idx] = h[b], h[b] = idx++; // 反向边
}

// 判断是否有增广路，如果有就将其建立出来
// 顺便建立分层图
bool bfs() {
    int hh = 0, tt = 0;
    memset(d, -1, sizeof d);
    q[0] = S, d[S] = 0, cur[S] = h[S];
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int ver = e[i];
            if (d[ver] == -1 && f[i]) {
                // ver点没有更新
                // ver的层次+1
                d[ver] = d[t] + 1;
                // 弧优化到当前弧
                cur[ver] = h[ver];
                if (ver == T) return true;
                q[++tt] = ver;
            }
        }
    }
    return false;
}

// 搜索从当前点出发，最多可以流的流量
// dfs搜索
ll find(int u, ll limit) {
    if (u == T) return limit;
    ll flow = 0;
    // cur[i]代表当前没有满的路径
    // 已经用过且满的路径不需要再搜索了
    // 增加flow<limit是一个显而易见的限制
    for (int i = cur[u]; ~i && flow < limit; i = ne[i]) {
        // 先记录一下当前搜索的弧
        cur[u] = i;  // 当前弧优化
        int ver = e[i];
        if (d[ver] == d[u] + 1 && f[i]) //当前点是再上一层图的下一层
        {
            int t = find(ver, min((ll) f[i], limit - flow));
            if (!t) d[ver] = -1; // 搜索失败，表示这个点到终点是没有路径的，赋值-1
            // 更新当前容量网络
            f[i] -= t, f[i ^ 1] -= t, flow += t;
        }
    }
    return flow;
}

ll dinic() {
    ll r = 0, flow;
    // 如果有增广路
    // 就把所有能够建立的增广路都建立出来
    // 再把其叠加起来
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r;
}

inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}  // 快读
#define debug true

int main() {
    int a1, a2, an, b1, b2, bn;
    while (scanf("%d%d%d%d%d%d%d", &n, &a1, &a2, &an, &b1, &b2, &bn) != EOF) {
        init();
        S = 0, T = 2 * n + 2;
        ++a1, ++a2, ++b1, ++b2;
        char g[55][55];
        for(int i = 1; i <= n; ++i){
            for(int j = 1; j <= n; ++j){
                scanf("%s", g[i]);
                if (debug) cout << g[i] << endl;
            }
            if (debug) cout << endl;
        }
        add(S, a1, an), add(a2 + n, T, an);
        add(S, b1, bn), add(b2 + n, T, bn);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (g[i][j-1] == 'X') continue;
                if (g[i][j-1] == 'O') add(i, j + n, 1);
                if (g[i][j-1] == 'N') add(i, j + n, INF);
            }
        }
        auto res1 = dinic();
        std::swap(S, T);
        add(S, a1+n, an), add(a2, T, an);
        add(S, b1+n, bn), add(b2, T, bn);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (g[i][j] == 'X') continue;
                if (g[i][j] == 'O') add(i + n, j, 1);
                if (g[i][j] == 'N') add(i + n, j, INF);
            }
        }
        auto res2 = dinic();
        if (debug)cout << "res1: " << res1 << " res2: " << res2 << endl;
        if (res1 != (an + bn) || res2 != (an + bn)) {
            cout << "No" << endl;
        } else {
            cout << "Yes" << endl;
        }
    }
    return 0;
}
