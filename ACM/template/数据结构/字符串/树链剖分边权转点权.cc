#include<bits/stdc++.h>

#define MAXN 200005
using namespace std;
int cnt, h[MAXN], ne[MAXN << 1], e[MAXN << 1], w[MAXN << 1], pre[MAXN << 1];
int n, a[MAXN], t[MAXN << 2], tag[MAXN << 2], cov[MAXN << 2];
int siz[MAXN], son[MAXN], dfn[MAXN], Index, top[MAXN], rk[MAXN], dep[MAXN], faz[MAXN];
// string s;

inline void add(int u, int v, int c) {
    ++cnt;
    e[cnt] = v, w[cnt] = c;
    ne[cnt] = h[u], h[u] = cnt, pre[cnt] = u;
}

void dfs1(int u) {
    siz[u] = 1;
    son[u] = 0;
    for (int i = h[u]; i; i = ne[i]) {
        int v = e[i];
        if (v == faz[u]) continue;
        faz[v] = u;
        dep[v] = dep[u] + 1;
        rk[v] = w[i];
        dfs1(v);
        siz[u] += siz[v];
        if (siz[son[u]] < siz[v]) son[u] = v;
    }
}

void dfs2(int u, int rt) {
    dfn[u] = ++Index;
    top[u] = rt;
    a[Index] = rk[u];
    if (son[u]) dfs2(son[u], rt);
    for (int i = h[u]; i; i = ne[i]) {
        int v = e[i];
        if (v == faz[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

void pushup(int rt) {
    t[rt] = max(t[rt << 1], t[rt << 1 | 1]);
}

void pushdown(int rt) {
    if (~cov[rt]) {
        cov[rt << 1] = cov[rt << 1 | 1] = cov[rt];
        t[rt << 1] = t[rt << 1 | 1] = cov[rt];
        tag[rt << 1] = tag[rt << 1 | 1] = 0;
        cov[rt] = -1;
    }
    tag[rt << 1] += tag[rt];
    tag[rt << 1 | 1] += tag[rt];
    t[rt << 1] += tag[rt];
    t[rt << 1 | 1] += tag[rt];
    tag[rt] = 0;
}

void BuildSegmentTree(int rt, int l, int r) {
    cov[rt] = -1;
    if (l == r) {
        t[rt] = a[l];
        return;
    }
    int mid = l + r >> 1;
    BuildSegmentTree(rt << 1, l, mid);
    BuildSegmentTree(rt << 1 | 1, mid + 1, r);
    pushup(rt);
}

void ModifyCover(int rt, int l, int r, int tl, int tr, int val) {
    if (tl <= l && r <= tr) {
        t[rt] = cov[rt] = val;
        tag[rt] = 0;
        return;
    }
    pushdown(rt);
    int mid = l + r >> 1;
    if (tl <= mid) ModifyCover(rt << 1, l, mid, tl, tr, val);
    if (tr > mid) ModifyCover(rt << 1 | 1, mid + 1, r, tl, tr, val);
    pushup(rt);
}

void ModifyAdd(int rt, int l, int r, int tl, int tr, int val) {
    if (tl <= l && r <= tr) {
        t[rt] += val;
        tag[rt] += val;
        return;
    }
    pushdown(rt);
    int mid = l + r >> 1;
    if (tl <= mid) ModifyAdd(rt << 1, l, mid, tl, tr, val);
    if (tr > mid) ModifyAdd(rt << 1 | 1, mid + 1, r, tl, tr, val);
    pushup(rt);
}

int query(int rt, int l, int r, int tl, int tr) {
    if (tl <= l && r <= tr) return t[rt];
    pushdown(rt);
    int mid = l + r >> 1, res = 0;
    if (tl <= mid) res = max(res, query(rt << 1, l, mid, tl, tr));
    if (tr > mid) res = max(res, query(rt << 1 | 1, mid + 1, r, tl, tr));
    return res;
}

void ModifyCoverOnTree(int u, int v, int val) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        ModifyCover(1, 1, n, dfn[top[u]], dfn[u], val);
        u = faz[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    ModifyCover(1, 1, n, dfn[u] + 1, dfn[v], val);
}

void ModifyAddOnTree(int u, int v, int val) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        ModifyAdd(1, 1, n, dfn[top[u]], dfn[u], val);
        u = faz[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    ModifyAdd(1, 1, n, dfn[u] + 1, dfn[v], val);
}

int queryMaxnOnTree(int u, int v) {
    int res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        res = max(res, query(1, 1, n, dfn[top[u]], dfn[u]));
        u = faz[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    res = max(res, query(1, 1, n, dfn[u] + 1, dfn[v]));
    return res;
}

inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}  // 快读


int main() {
    n = read();
    for (int i = 1; i < n; i++) {
        int x = read(), y = read(), z = read();
        add(x, y, z), add(y, x, z);
    }
    dfs1(1);
    dfs2(1, 1);
    BuildSegmentTree(1, 1, n);
    char op[12];
    while (scanf("%s", op) && std::strcmp(op, "Stop") != 0) {
        int x, y, z;
        x = read(), y = read();
        if (!std::strcmp(op, "Change")) {
            x <<= 1;
            int u = pre[x], v = e[x];
            if (dep[u] > dep[v]) swap(u, v);
            ModifyCoverOnTree(u, v, y);
        } else if (!std::strcmp(op, "Cover")) {
            z = read();
            ModifyCoverOnTree(x, y, z);
        } else if (!std::strcmp(op, "Add")) {
            z = read();
            ModifyAddOnTree(x, y, z);
        } else if (!std::strcmp(op, "Max")) {
            printf("%d\n", queryMaxnOnTree(x, y));
        }

    }
    return 0;
}
