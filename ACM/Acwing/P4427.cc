#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ll = long long;
const int N = 3e5 + 100, M = N << 1;

int n, m;
int h[N], w[N], e[M], ne[M], idx; //建树
int id[N], nw[N], cnt; //id:节点的dfn序编号，nw[id[i]]是i的权值w（w -> nw的映射）
int dep[N], sz[N], top[N], fa[N], son[N], pos[N]; // pos 线段树上点对应dfn的点
constexpr int K = 51, mod = 998244353;
//sz:子树节点个数，top:重链的顶点，son:重儿子，fa:父节点
struct Node {
    int l, r;
    ll sum[K];
} tr[N << 2];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

ll qsm(int a, int b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return res;
}

int qpow(int a, int b) {
    int ans = 1;

    while (b) {
        if (b & 1)
            ans = 1ll * ans * a % mod;

        a = 1ll * a * a % mod;
        b >>= 1;
    }

    return ans;
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
    id[u] = ++cnt, nw[cnt] = w[u], top[u] = t, pos[cnt] = u;
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
    for (int i = 1; i < K; ++i)
        tr[u].sum[i] = (tr[u << 1].sum[i] + tr[u << 1 | 1].sum[i]) % mod;
}

void pushdown(int u) {
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    // todo
}

void build(int u, int l, int r) {
    tr[u] = {l, r};
    if (l == r) {
        int d = dep[pos[l]];
        // cout << "l: " << l << " pos: " << pos[l] <<" dep:" <<d<<endl;
        for (int i = 1; i < K; ++i) {
            tr[u].sum[i] = qpow(d, i) % mod;
        }
        // cout <<"k:45 " << "sum: " << tr[u].sum[45] << endl;
        return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

ll query(int u, int l, int r, int k) {
    if (l <= tr[u].l && r >= tr[u].r) {
        // cout << "pos[l]: " << pos[tr[u].l] << " pos[r]: " << pos[tr[u].r] << endl;
        // cout << "query " << " l: " << tr[u].l << " r:" << tr[u].r << endl;
        // cout <<"add " << tr[u].sum[k] <<" k:"<< k<< endl;
        return tr[u].sum[k];
    }
    pushdown(u);
    int mid = (tr[u].l + tr[u].r) >> 1;
    ll res = 0;
    if (l <= mid) res = (res + query(u << 1, l, r, k)) % mod;
    if (r > mid) res = (res + query(u << 1 | 1, l, r, k)) % mod;
    return res;
}


ll query_path(int u, int v, int k) {
    ll res = 0;
    while (top[u] != top[v])    //向上爬找到相同重链
    {
        // cout << "u: " << u << " top[u]: " << top[u] << " v:" << v << " top[v]: " << top[v] << endl;
        if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
        // cout <<"query " << " l:" << id[top[u]] <<" r:" << id[u] << endl;
        res = (res + query(1, id[top[u]], id[u], k)) % mod;
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) std::swap(u, v);
    res = (res + query(1, id[v], id[u], k)) % mod;  //在同一重链中，处理剩余区间
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

inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}  // 快读


int main() {
    // fhj();
    memset(h, -1, sizeof h);
    n = read();
    for (int i = 1; i < n; ++i) {
        int x = read(), y = read();
        add(y, x), add(x, y);
    }
    dfs1(1, -1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    m = read();
    while (m--) {
        int u = read(), v = read(), k = read();
        cout << query_path(u, v, k) << endl;
    }
    return 0;
}
