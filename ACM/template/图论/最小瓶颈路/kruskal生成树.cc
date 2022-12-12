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

/*
#include <bits/stdc++.h>
#define MAXN 100005
#define MOD 1000000007
using namespace std;
struct Edge {
    int u, v, w, nxt;
    bool operator<(const Edge t) const {
        return w < t.w;
    }
} t[MAXN], e[MAXN << 2];
int n, m, k, head[MAXN << 1], pos, u, v, idx, cnt, f[MAXN << 1], val[MAXN << 1];
int A, B, C, P, ans, dep[MAXN << 2], seq[MAXN << 2], in[MAXN << 2], st[21][MAXN << 2];
void addEdge(int u, int v, int w) {
    e[++pos] = {u, v, w, head[u]};
    head[u] = pos;
}
int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}
void build() {
    sort(t + 1, t + m + 1);
    idx = n;

    for (int i = 1, cnt = 0; cnt < n - 1 && i <= m; i++)
        if (find(t[i].u) != find(t[i].v)) {
            int fa = find(t[i].u), fb = find(t[i].v);
            f[fa] = f[fb] = ++idx;
            cnt++;
            addEdge(fa, idx, 0), addEdge(idx, fa, 0);
            addEdge(fb, idx, 0), addEdge(idx, fb, 0);
            val[idx] = t[i].w;
        }
}
void dfs(int u, int f = 0, int d = 1) {
    seq[++cnt] = u, dep[cnt] = d, in[u] = cnt;

    for (int i = head[u]; i; i = e[i].nxt) {
        if (e[i].v == f)
            continue;

        dfs(e[i].v, u, d + 1);
        seq[++cnt] = u, dep[cnt] = d;
    }
}

void init() {
    for (int i = 1; i <= cnt; i++)
        st[0][i] = i;

    for (int i = 1; i <= __lg(cnt); i++)
        for (int j = 1; j + (1 << i) - 1 <= cnt; j++) {
            int l = st[i - 1][j], r = st[i - 1][j + (1 << (i - 1))];
            st[i][j] = dep[l] < dep[r] ? l : r;
        }
}
int LCA(int u, int v) {
    int l = in[u], r = in[v];

    if (l > r)
        swap(l, r);

    int s = __lg(r - l + 1);
    int a = st[s][l], b = st[s][r - (1 << s) + 1];
    return dep[a] < dep[b] ? seq[a] : seq[b];
}

inline int rnd() {
    return A = (A * B + C) % P;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("data/data1.in", "r", stdin);
    // freopen("data/data1.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= 2 * n; i++)
        f[i] = i;

    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &t[i].u, &t[i].v, &t[i].w);

    build();
    dfs(idx);
    init();
    scanf("%d%d%d%d%d", &k, &A, &B, &C, &P);

    while (k--) {
        int u = rnd() % n + 1, v = rnd() % n + 1;
        ans = (ans + val[LCA(u, v)]) % MOD;
    }

    printf("%d", ans);
    return 0;
}
*/