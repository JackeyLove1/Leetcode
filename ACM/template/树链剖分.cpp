#include <iostream>
#include <cstring>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10, M = N << 1;

int n, m;
int h[N], w[N], e[M], ne[M], idx; //建树
int id[N], nw[N], cnt; //id:节点的dfs序编号，nw[id[i]]是i的权值w（w -> nw的映射）
int dep[N], sz[N], top[N], fa[N], son[N];
//sz:子树节点个数，top:重链的顶点，son:重儿子，fa:父节点
struct SegmentTree
{
    int l, r;
    LL sum, flag;
}tr[N << 2];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}
//dfs1预处理
// 求出当前节点的子节点的数目，深度，和对应的重节点
// 求每个点的重儿子是谁
void dfs1(int u, int father, int depth)
{
    dep[u] = depth, fa[u] = father, sz[u] = 1;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j == father) continue;
        dfs1(j, u, depth + 1);
        sz[u] += sz[j];
        if (sz[son[u]] < sz[j]) son[u] = j; //重儿子是子树节点最多的儿子
    }
}

//dfs2做剖分（t是重链的顶点）
// 求出当前点所在重链的编号
// 求dfs序
void dfs2(int u, int t)
{
    // top[u]当前点所在重链的顶点为t
    // dfs序列数组id,和权值数组nw
    id[u] = ++ cnt, nw[cnt] = w[u], top[u] = t;
    if (!son[u]) return; //叶节点结束
    dfs2(son[u], t); //优先搜索重儿子，重儿子重链剖分
    //处理轻儿子
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j == fa[u] || j == son[u]) continue;
        dfs2(j, j); //轻儿子的重链顶点就是他自己
    }
}

//------------------------线段树的部分------------------------\\

void pushup(int u)
{
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void pushdown(int u)
{
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    if (root.flag)
    {
        left.sum += root.flag * (left.r - left.l + 1);
        left.flag += root.flag;
        right.sum += root.flag * (right.r - right.l + 1);
        right.flag += root.flag;
        root.flag = 0;
    }
}

// 用重连剖分的dfs序构建线段树
void build(int u, int l, int r)
{
    tr[u] = {l, r, nw[r], 0};
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

void update(int u, int l, int r, int k)
{
    if (l <= tr[u].l && r >= tr[u].r)
    {
        tr[u].flag += k;
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

//------------------------树链剖分------------------------\\

void update_path(int u, int v, int k)
{
    while (top[u] != top[v])    //向上爬找到相同重链
    {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        update(1, id[top[u]], id[u], k);    
        //dfs序原因，上面节点的id必然小于下面节点的id
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    update(1, id[v], id[u], k); //在同一重链中，处理剩余区间
}
LL query_path(int u, int v)
{
    LL res = 0;
    while (top[u] != top[v])    //向上爬找到相同重链
    {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        res += query(1, id[top[u]], id[u]);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    res += query(1, id[v], id[u]);  //在同一重链中，处理剩余区间
    return res;
}
void update_tree(int u, int k) //子树全部加上k
{
    update(1, id[u], id[u] + sz[u] - 1, k); 
    //由于dfs序的原因，可以利用子树节点个数直接找到区间
}
LL query_tree(int u)
{
    // 左节点id[u], 右节点id[u] + sz[u] - 1
    return query(1, id[u], id[u] + sz[u] - 1); //原因同上
}

int main()
{
    scanf("%d", &n);
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]);
    for (int i = 1; i <  n; i ++ )
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

/*
// yxc

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
    LL add, sum;
} tr[N * 4];

inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs1(int u, int father, int depth) {
    dep[u] = depth, fa[u] = father, sz[u] = 1;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == father) continue;
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
    if (root.add) {
        left.add += root.add, left.sum += root.add * (left.r - left.l + 1);
        right.add += root.add, right.sum += root.add * (right.r - right.l + 1);
        root.add = 0;
    }
}

void build(int u, int l, int r) {
    tr[u] = {l, r, 0, nw[r]};
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
    for (int i = 1; i <= n; i++) cin >> w[i];
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    dfs1(1, -1, 1);
    dfs2(1, 1);
    build(1, 1, n);

    cin >> m;
    while (m--) {
        int t, u, v, k;
        cin >> t >> u;
        if (t == 1) {
            cin >> v >> k;
            update_path(u, v, k);
        } else if (t == 2) {
            cin >> k;
            update_tree(u, k);
        } else if (t == 3) {
            cin >> v;
            printf("%lld\n", query_path(u, v));
        } else printf("%lld\n", query_tree(u));
    }

    return 0;
}


*/