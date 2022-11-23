#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 100010, M = N * 2;

int n, m;
int w[N], h[N], e[M], ne[M], idx;
int id[N], nw[N], cnt;
int dep[N], sz[N], top[N], fa[N], son[N];
struct Tree
{
    int l, r;
    LL add, sum;
}tr[N * 4];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs1(int u, int father, int depth)
{
    dep[u] = depth, fa[u] = father, sz[u] = 1;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j == father) continue;
        dfs1(j, u, depth + 1);
        sz[u] += sz[j];
        if (sz[son[u]] < sz[j]) son[u] = j;
    }
}

void dfs2(int u, int t)
{
    id[u] = ++ cnt, nw[cnt] = w[u], top[u] = t;
    if (!son[u]) return;
    dfs2(son[u], t);
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j == fa[u] || j == son[u]) continue;
        dfs2(j, j);
    }
}

void pushup(int u)
{
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void pushdown(int u)
{
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    if (root.add)
    {
        left.add += root.add, left.sum += root.add * (left.r - left.l + 1);
        right.add += root.add, right.sum += root.add * (right.r - right.l + 1);
        root.add = 0;
    }
}

void build(int u, int l, int r)
{
    tr[u] = {l, r, 0, nw[r]};
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

void update(int u, int l, int r, int k)
{
    if (l <= tr[u].l && r >= tr[u].r)
    {
        tr[u].add += k;
        tr[u].sum += k * (tr[u].r - tr[u].l + 1);
        return;
    }
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid) update(u << 1, l, r, k);
    if (r > mid) update(u << 1 | 1, l, r, k);
    pushup(u);
}

LL query(int u, int l, int r)
{
    if (l <= tr[u].l && r >= tr[u].r) return tr[u].sum;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    LL res = 0;
    if (l <= mid) res += query(u << 1, l, r);
    if (r > mid) res += query(u << 1 | 1, l, r);
    return res;
}

void update_path(int u, int v, int k)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        update(1, id[top[u]], id[u], k);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    update(1, id[v], id[u], k);
}

LL query_path(int u, int v)
{
    LL res = 0;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        res += query(1, id[top[u]], id[u]);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    res += query(1, id[v], id[u]);
    return res;
}

void update_tree(int u, int k)
{
    update(1, id[u], id[u] + sz[u] - 1, k);
}

LL query_tree(int u)
{
    return query(1, id[u], id[u] + sz[u] - 1);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]);
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i ++ )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }
    dfs1(1, -1, 1);
    dfs2(1, 1);
    build(1, 1, n);

    scanf("%d", &m);
    while (m -- )
    {
        int t, u, v, k;
        scanf("%d%d", &t, &u);
        if (t == 1)
        {
            scanf("%d%d", &v, &k);
            update_path(u, v, k);
        }
        else if (t == 2)
        {
            scanf("%d", &k);
            update_tree(u, k);
        }
        else if (t == 3)
        {
            scanf("%d", &v);
            printf("%lld\n", query_path(u, v));
        }
        else printf("%lld\n", query_tree(u));
    }

    return 0;
}