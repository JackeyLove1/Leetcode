#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ll = long long;
const int N = 1e5 + 10, M = N << 1;
#define lson(u) tr[u << 1]
#define rson(u) tr[u << 1 | 1]
int n, m;
int h[N], w[N], e[M], ne[M], idx; //建树
int id[N], nw[N], cnt; //id:节点的dfn序编号，nw[id[i]]是i的权值w（w -> nw的映射）
int dep[N], sz[N], top[N], fa[N], son[N];
//sz:子树节点个数，top:重链的顶点，son:重儿子，fa:父节点
struct Node {
    ll l, r;
    ll sum, add;
} tr[N << 2];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

//dfs1预处理
void dfs1(int u, int father, int depth) {
    dep[u] = depth, fa[u] = father, sz[u] = 1;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == father) continue;
        dfs1(j, u, depth + 1);
        sz[u] += sz[j];
        if (sz[son[u]] < sz[j]) son[u] = j; //重儿子是子树节点最多的儿子
    }
}

//dfs2做剖分（t是重链的顶点）
void dfs2(int u, int t) {
    id[u] = ++cnt, nw[cnt] = w[u], top[u] = t;
    // cout << "u: " << u << " id:" << id[u] << " nw:" << nw[cnt] << " top:" << top[u] << endl;
    if (!son[u]) return; //叶节点结束
    dfs2(son[u], t); //重儿子重链剖分
    //处理轻儿子
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == fa[u] || j == son[u]) continue;
        dfs2(j, j); //轻儿子的重链顶点就是他自己
    }
}

void pushup(int u) {
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void pushdown(int u) {
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    if (root.add) {
        left.sum += root.add * (left.r - left.l + 1);
        left.add += root.add;
        right.sum += root.add * (right.r - right.l + 1);
        right.add += root.add;
        root.add = 0;
    }
}

void build(int u, int l, int r) {
    tr[u] = {l, r, nw[r], 0};
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

void update(int u, int l, int r, int k) {
    if (l <= tr[u].l && r >= tr[u].r) {
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

ll query(int u, int l, int r) {
    if (l <= tr[u].l && r >= tr[u].r) return tr[u].sum;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    ll res = 0;
    if (l <= mid) res += query(u << 1, l, r);
    if (r > mid) res += query(u << 1 | 1, l, r);
    return res;
}

void update_path(int u, int v, int k) {
    while (top[u] != top[v])    //向上爬找到相同重链
    {
        if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
        update(1, id[top[u]], id[u], k);    //dfs序原因，上面节点的id必然小于下面节点的id
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) std::swap(u, v);
    update(1, id[v], id[u], k); //在同一重链中，处理剩余区间
}

ll query_path(int u, int v) {
    ll res = 0;
    while (top[u] != top[v])    //向上爬找到相同重链
    {
        // cout << "u: " << u << " top[u]: " << top[u] << " v:" << v << " top[v]: " << top[v] << endl;
        if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
        // cout <<"query " << " l:" << id[top[u]] <<" r:" << id[u] << endl;
        res += query(1, id[top[u]], id[u]);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) std::swap(u, v);
    res += query(1, id[v], id[u]);  //在同一重链中，处理剩余区间
    return res;
}

inline int LCA(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] > dep[top[v]])
            u = fa[top[u]];
        else
            v = fa[top[v]];
    }
    return dep[u] > dep[v] ? v : u;
}

void update_tree(int u, int k) //子树全部加上k
{
    update(1, id[u], id[u] + sz[u] - 1, k); //由于dfs序的原因，可以利用子树节点个数直接找到区间
}

ll query_tree(int u) {
    return query(1, id[u], id[u] + sz[u] - 1); //原因同上
}

inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}  // 快读


int main() {
    // fhj();
    memset(h, -1, sizeof h);
    n = read(), m = read();
    for (int i = 1; i <= n; ++i) cin >> w[i];
    for (int i = 1; i < n; ++i) {
        int x = read(), y = read();
        add(x, y), add(y, x);
    }
    dfs1(1, -1, 1);
    dfs2(1, 1);
    build(1, 1, n);
    while (m--) {
        int op, x, k;
        op = read();
        // cout << "op: " << op << endl;
        if (op == 1) {
            x = read(), k = read();
            update_path(x, x, k);
        } else if (op == 2) {
            x = read(), k = read();
            update_tree(x, k);
        } else {
            x = read();
            printf("%lld\n", query_path(1, x));
        }
    }
    return 0;
}
