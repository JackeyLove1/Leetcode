#include <bits/stdc++.h>
#define MAXN 100005
#define INF 0x3f3f3f3f
using namespace std;
struct Edge {
    int u, v, w, nxt;
    bool operator<(const Edge t) const {
        return w < t.w;
    }
} t[MAXN], e[MAXN];
int n, m, k, head[MAXN], pos, u, v, f[MAXN], fa[21][MAXN], st[21][MAXN], dep[MAXN], ans;
void addEdge(int u, int v, int w) {
    e[++pos] = {u, v, w, head[u]};
    head[u] = pos;
}
int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}
void merge(int a, int b) {
    f[find(a)] = find(b);
}
void build() {
    sort(t + 1, t + m + 1);

    for (int i = 1, cnt = 0; cnt < n - 1 && i <= m; i++)
        if (find(t[i].u) != find(t[i].v)) {
            merge(t[i].u, t[i].v);
            addEdge(t[i].u, t[i].v, t[i].w);
            addEdge(t[i].v, t[i].u, t[i].w);
            cnt++;
        }
}
void dfs(int u, int f = 0) {
    fa[0][u] = f, dep[u] = dep[f] + 1;

    for (int i = head[u]; i; i = e[i].nxt) {
        if (f == e[i].v)
            continue;

        dfs(e[i].v, u);
        st[0][e[i].v] = e[i].w;
    }
}
int LCA(int u, int v) {
    if (dep[u] < dep[v])
        swap(u, v);

    while (dep[u] != dep[v])
        u = fa[__lg(dep[u] - dep[v])][u];

    if (u == v)
        return u;

    for (int i = __lg(dep[u]); i >= 0; i--)
        if (fa[i][u] != fa[i][v])
            u = fa[i][u], v = fa[i][v];

    return fa[0][u];
}
int query(int u, int lca) {
    int res = 0;

    for (int i = __lg(n); i >= 0; i--)
        if (dep[fa[i][u]] >= dep[lca])
            res = max(res, st[i][u]), u = fa[i][u];

    return res;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("data/data1.in", "r", stdin);
    // freopen("data/data1.out", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &k);

    for (int i = 1; i <= n; i++)
        f[i] = i;

    memset(st, 0, sizeof st);

    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &t[i].u, &t[i].v, &t[i].w);

    build();
    int tmp = 0;

    for (int i = 1; i <= n; i++)
        if (!fa[0][i])
            dfs(i);

    for (int i = 1; i <= __lg(n); i++)
        for (int j = 1; j <= n; j++) {
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
            st[i][j] = max(st[i - 1][j], st[i - 1][fa[i - 1][j]]);
        }

    while (k--) {
        scanf("%d%d", &u, &v);
        int lca = LCA(u, v);
        int t1 = query(u, lca), t2 = query(v, lca);
        int ans = max(t1, t2);

        if (find(u) != find(v))
            ans = -1;

        printf("%d\n", ans);
    }

    return 0;
}