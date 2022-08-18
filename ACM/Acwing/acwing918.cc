#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <unordered_set>


using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ull = unsigned long long;
using LL = long long;
using PII = pair<int, int>;

const int N = 100010, M = N * 2;

int n, m;
int w[N], h[N], e[M], ne[M], idx;
int id[N], nw[N], cnt;
int dep[N], sz[N], top[N], fa[N], son[N];
struct Tree {
    int l, r;
    int flag;
    LL sum;
} tr[N * 4];

inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs1(int u, int father, int depth) {
    dep[u] = depth, sz[u] = 1;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        dfs1(j, u, depth + 1);
        sz[u] += sz[j];
        if (sz[son[u]] < sz[j]) son[u] = j;
    }
}

void dfs2(int u, int t) {

    id[u] = ++cnt, nw[cnt] = w[u], top[u] = t;
    if (!son[u]) return;
    dfs2(son[u], t);
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == fa[u] || j == son[u]) continue;
        dfs2(j, j);
    }
}

inline void pushup(int u) {
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

inline void pushdown(int u) {
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    if (root.flag != -1) {
        left.sum = root.flag * (left.r - left.l + 1);
        right.sum = root.flag * (right.r - right.l + 1);
        left.flag = right.flag = root.flag;
        root.flag = -1;
    }
}

void build(int u, int l, int r) {
    tr[u] = {l, r, -1, 0};
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

void update(int u, int l, int r, int k) {
    if (l <= tr[u].l && r >= tr[u].r) {
        tr[u].flag = k;
        tr[u].sum = k * (tr[u].r - tr[u].l + 1);
        return;
    }
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid) update(u << 1, l, r, k);
    if (r > mid) update(u << 1 | 1, l, r, k);
    pushup(u);
}

LL query(int u, int l, int r) {
    if (l <= tr[u].l && r >= tr[u].r) return tr[u].sum;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    LL res = 0;
    if (l <= mid) res += query(u << 1, l, r);
    if (r > mid) res += query(u << 1 | 1, l, r);
    return res;
}

void update_path(int u, int v, int k) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        update(1, id[top[u]], id[u], k);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    update(1, id[v], id[u], k);
}

LL query_path(int u, int v) {
    LL res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        res += query(1, id[top[u]], id[u]);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    res += query(1, id[v], id[u]);
    return res;
}

void update_tree(int u, int k) {
    update(1, id[u], id[u] + sz[u] - 1, k);
}

LL query_tree(int u) {
    return query(1, id[u], id[u] + sz[u] - 1);
}

int main() {
    fhj();
    cin >> n;
    // for (int i = 1; i <= n; i++) cin >> w[i];
    memset(w, 0, sizeof w);
    memset(h, -1, sizeof h);
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        ++p;
        add(p, i);
        fa[i] = p;
    }
    dfs1(1, -1, 1);
    dfs2(1, 1);
    build(1, 1, n);

    cin >> m;
    string op;
    int x;
    while (m--) {
        cin >> op >> x;
        ++x;
        if (op == "install") {
            auto origin = query_tree(1);
            update_path(1, x, 1);
            cout << query_tree(1) - origin << endl;
        } else {
            auto origin = query_tree(1);
            update_tree(x, 0);
            cout << origin - query_tree(1) << endl;
        }
    }

    return 0;
}