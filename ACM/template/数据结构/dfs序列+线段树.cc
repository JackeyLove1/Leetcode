#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 5;
struct Edge {
    int u, v, next;
} e[MAXN << 1];
int n, m, rt, idx, pos, head[MAXN], in[MAXN], out[MAXN], dep[MAXN], st[MAXN][21];
long long w[MAXN], C[2][MAXN];
void addEdge(int u, int v) {
    e[++pos] = {u, v, head[u]};
    head[u] = pos;
}

void dfs(int u, int fa = 0) {
    in[u] = ++idx;
    st[u][0] = fa, dep[u] = dep[fa] + 1;

    for (int i = 1; i <= __lg(dep[u]); i++)
        st[u][i] = st[st[u][i - 1]][i - 1];

    for (int i = head[u]; i; i = e[i].next)
        if (e[i].v != fa)
            dfs(e[i].v, u);

    out[u] = idx;
}

int LCA(int u, int v) {
    if (dep[u] < dep[v])
        swap(u, v);

    while (dep[u] != dep[v])
        u = st[u][__lg(dep[u] - dep[v])];

    if (u == v)
        return u;

    for (int i = __lg(dep[u]); i >= 0; i--)
        if (st[u][i] != st[v][i])
            u = st[u][i], v = st[v][i];

    return st[u][0];
}

int lowbit(int x) {
    return x & -x;
}

void update(int f, int x, long long val) {
    if (!x)
        return;

    for (int i = x; i <= n; i += lowbit(i))
        C[f][i] += val;
}

long long query(int f, int x) {
    long long res = 0;

    for (int i = x; i > 0; i -= lowbit(i))
        res += C[f][i];

    return res;
}

void updateNode(int u, long long k) {
    update(0, in[u], k), update(0, out[u] + 1, -k);
}

long long queryT(int u) {
    return query(1, in[u]) * dep[u] + query(0, in[u]);
}

long long queryChain(int u, int v) {
    int lca = LCA(u, v), flca = st[lca][0];
    return queryT(u) + queryT(v) - queryT(lca) - queryT(flca);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("data.in", "r", stdin);
    // freopen("data.out", "w", stdout);
#endif
    scanf("%d %d %d", &n, &m, &rt);

    for (int i = 1; i <= n; i++)
        scanf("%lld", w + i);

    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v), addEdge(v, u);
    }

    dfs(rt);

    for (int i = 1; i <= n; i++)
        updateNode(i, w[i]);

    while (m--) {
        int opt, a, b;
        scanf("%d %d %d", &opt, &a, &b);

        if (opt == 1)
            updateNode(a, b);
        else if (opt == 2) {
            update(1, in[a], b), update(1, out[a] + 1, -b);
            updateNode(a, -1LL * b * (dep[a] - 1));
        } else
            printf("%lld\n", queryChain(a, b));
    }

    return 0;
}