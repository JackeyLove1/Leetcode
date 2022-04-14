#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <unordered_set>
#include <cmath>
#include <numeric>
#include <cstring>
#include <queue>
#include <string>

using namespace std;

template<typename T>
static inline void print(vector<T> &vec) {
    for_each(vec.begin(), vec.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ll = long long;

const int N = 1e5 + 6;

int n, m;

// quickly power
ll qpow(ll a, ll b, ll p) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

// quickly multiply
ll qmul(ll a, ll b, ll p) {
    ll res = 0;
    while (b) {
        if (b & 1) res = (res + a) % p;
        a = (a + a) % p;
        b >>= 1;
    }
    return res;
}

namespace graph {
    int h[N], ne[N], e[N], w[N], idx;

    inline void init() {
        idx = 0;
        memset(h, -1, sizeof h);
    }

    inline void add(int a, int b) {
        e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    }

    int match[N], st[N];

    // bipartite graph matching
    int find_matching(int x) {
        for (int i = h[x]; i != -1; i = ne[i]) {
            int j = e[i];
            if (!st[j]) {
                st[j] = true;
                if (!match[j] || find_matching(match[j])) {
                    match[j] = x;
                    return true;
                }
            }
        }
        return false;
    }

    // DFS
    void dfs(int u) {
        st[u] = true;
        for (int i = h[u]; i != -1; i = ne[i]) {
            int j = e[i];
            if (!st[j]) dfs(j);
        }
    }

    // BFS
    void bfs() {
        queue<int> q;
        st[1] = true;
        q.push(1);
        while (!q.empty()) {
            auto t = q.front();
            q.pop();
            for (int i = h[t]; i != -1; i = ne[i]) {
                int j = e[i];
                if (!st[j]) {
                    st[j] = true;
                    q.push(j);
                }
            }
        }
    }

    //  diameter of the tree
    int f[N];

    void diameter(int u, int fa) {
        f[u] = 0;
        for (int i = h[u]; i != -1; i = ne[i]) {
            int j = e[i];
            if (j == fa) continue;
            diameter(j, u);
            f[u] = max(f[u], f[j] + w[i]);
        }
    }

    // longest and sublongest diameter
    int dfs2(int u, int fa) {
        int dist = 0;
        int d1 = 0, d2 = 0;
        for (int i = h[u]; i != -1; i = ne[i]) {
            int j = e[i];
            if (j == fa) continue;
            int d = dfs2(j, u) + w[i];
            dist = max(dist, d);
            if (d > d1) d2 = d1, d1 = d;
            else if (d > d2) d2 = d;
        }
        dist = max(dist, d1 + d2);
        return dist;
    }

    int d[N];

    bool topsort() {
        queue<int> q;
        for (int i = 1; i <= n; ++i) {
            if (!d[i]) {
                q.push(i);
            }
        }
        while (!q.empty()) {
            int t = q.front();
            for (int i = h[t]; i != -1; i = ne[i]) {
                int j = e[i];
                if (--d[j] == 0) {
                    q.push(j);
                }
            }
        }
        return q.empty();
    }

    // Dijkstra
    int dist[N];
    constexpr int INF = 0x3f3f3f3f;

    int dijkstra() {
        using PII = pair<int, int>;
        memset(dist, 0x3f, sizeof dist);
        priority_queue<PII, vector<PII>, greater<>> heap;
        dist[1] = 0;
        heap.push({1, 0}); // ver, dist
        while (!heap.empty()) {
            auto t = heap.top();
            heap.pop();
            int ver = t.first;
            for (int i = h[ver]; i != -1; i = ne[i]) {
                int j = e[i];
                if (dist[j] > dist[ver] + w[i]) {
                    dist[j] = dist[ver] + w[i];
                    heap.push({j, dist[j]});
                }
            }
        }
        if (dist[n] >= INF / 2) return -1;
        return dist[n];
    }

    // SPFA
    int spfa() {
        memset(dist, 0x3f, sizeof dist);
        dist[1] = 0;
        queue<int> q;
        q.push(1);
        st[1] = true;
        while (!q.empty()) {
            auto t = q.front();
            q.pop();
            st[t] = false;
            for (int i = h[t]; i != -1; i = ne[i]) {
                int j = e[i];
                if (dist[j] > dist[t] + w[i]) {
                    dist[j] = dist[t] + w[i];
                    if (!st[j]) {
                        q.push(j);
                        st[j] = true;
                    }
                }
            }
        }
        if (dist[n] >= INF / 2) return -1;
        return dist[n];
    }

    // Floyed
    int g[N][N];

    void floyed_init() {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i == j) g[i][j] = 0;
                else g[i][j] = INF;
            }
        }
    }

    void floyed() {
        for (int k = 1; k <= n; ++k) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
                }
            }
        }
    }

    // Prim
    int prim() {
        memset(dist, 0x3f, sizeof dist);
        int res = 0;
        for (int i = 0; i < n; ++i) {
            int t = -1;
            for (int j = 1; j <= n; ++j) {
                if (!st[j] && (t == -1 || dist[t] > dist[j])) {
                    t = j;
                }
            }
            if (i && dist[t] == INF) return INF;
            if (i) res += dist[t];
            st[t] = true;
            for (int j = 1; j <= n; ++j) dist[j] = min(dist[j], g[t][j]);
        }
        return res;
    }

    // kruskal
    int p[N], fa[N];
    int n, m;
    constexpr int M = 1e6 + 1;

    struct Edge {
        int a, b, w;

        bool operator<(const Edge &rhs) const {
            return w < rhs.w;
        }
    } edges[M];

    int find(int x) {
        if (p[x] != x) return p[x] = find(p[x]);
        return p[x];
    }

    int kruskal() {
        sort(edges, edges + m);
        for (int i = 1; i <= n; ++i) {
            fa[i] = i;
        }
        int res = 0, cnt = 0;
        for (int i = 0; i < m; ++i) {
            int a = edges[i].a, b = edges[i].b, w = edges[i].w;
            a = find(a), b = find(b);
            if (a != b) {
                fa[a] = b;
                res += w;
                cnt++;
            }
        }
        if (cnt < n - 1) {
            return INF;
        }
        return res;
    }

}

namespace color {
    int n;
    int h[N], e[N], ne[N], w[N], idx;
    int color[N];

    inline void init() {
        memset(h, -1, sizeof h);
        idx = 0;
    }

    bool dfs(int u, int c) {
        color[u] = c;
        for (int i = h[u]; i != -1; i = ne[i]) {
            int j = e[i];
            if (color[j] == -1) {
                if (!dfs(j, !c)) return false;
            } else if (color[j] == c) return false;
        }
        return true;
    }

    bool check() {
        memset(color, -1, sizeof color);
        bool flag = true;
        for (int i = 1; i <= n; ++i) {
            if (color[i] == -1) {
                if (!dfs(i, 0)) {
                    flag = false;
                    break;
                }
            }
        }
        return flag;
    }
}

namespace binary {
    int n1, n2;
    bool st[N];
    int h[N], e[N], w[N], ne[N], idx;
    int match[N];

    inline void add(int a, int b, int c) {
        e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
    }

    bool find(int t) {
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (!st[j]) {
                st[j] = true;
                if (match[j] == 0 || find(match[j])) {
                    match[j] = t;
                    return true;
                }
            }
        }
        return false;
    }

    int check() {
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            memset(st, false, sizeof st);
            if (find(i)) res++;
        }
        return res;
    }
}

namespace segmentTree {
    int m, p;
    struct Node {
        int l, r;
        int v;
    } tr[N * 4];

    static inline int max(int a, int b) {
        return a > b ? a : b;
    }

    void pushup(int u) {
        tr[u].v = max(tr[u << 1].v, tr[u << 1 | 1].v);
    }

    void build(int u, int l, int r) {
        tr[u] = {l, r};
        if (l == r) return;
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    }

    int query(int u, int l, int r) {
        if (tr[u].l >= l && tr[u].r <= r) return tr[u].v;
        int mid = tr[u].l + tr[u].r >> 1;
        int v = 0;
        if (l <= mid) v = query(u << 1, l, r);
        if (r > mid) v = max(v, query(u << 1 | 1, l, r));
        return v;
    }

    void modify(int u, int x, int v) {
        if (tr[u].l == x && tr[u].r == x) tr[u].v = v;
        else {
            int mid = tr[u].l + tr[u].r >> 1;
            if (x < mid) modify(u << 1, x, v);
            if (x >= mid) modify(u << 1 | 1, x, v);
            pushup(u);
        }
    }

}

namespace LazyTagSegment {
    using ll = long long;
    int n, m;
    int w[N];
    struct node {
        int l, r;
        ll sum, add;
    } tr[N * 4];

    void pushup(int u) {
        tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
    }

    void pushdown(int u) {
        auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
        if (root.add) {
            left.add += root.add, left.sum += root.add * (left.r - left.l + 1);
            right.add += root.add, right.sum += root.add * (right.r - right.l + 1);
            root.add = 0;
        }
    }

    void build(int u, int l, int r) {
        if (l == r) tr[u] = {l, r, 0, 0};
        else {
            tr[u] = {l, r};
            int mid = l + r >> 1;
            build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
            pushup(u);
        }
    }

    void modify(int u, int l, int r, int d) {
        if (tr[u].l >= l && tr[u].r <= r) {
            tr[u].sum += (tr[u].r - tr[u].l + 1) * d;
            tr[u].add += d;
        } else {
            pushdown(u);
            int mid = tr[u].l + tr[u].r >> 1;
            if (l <= mid) modify(u << 1, l, r, d);
            if (r > mid) modify(u << 1 | 1, l, r, d);
            pushup(u);
        }
    }

    ll query(int u, int l, int r) {
        if (tr[u].l >= l && tr[u].r <= r) return tr[u].sum;
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        ll sum = 0;
        if (l <= mid) sum += query(u << 1, l, r);
        if (r > mid) sum += query(u << 1 | 1, l, r);
        return sum;
    }
}

namespace lowbitTree {
    int n;
    int tree[N];

    inline int lowbit(int x) {
        return x & (-x);
    }

    inline void add(int x, int k) {
        for (int pos = x; pos <= n; pos += lowbit(pos)) {
            tree[pos] += k;
        }
    }

    inline int query(int x) {
        int res = 0;
        for (int pos = x; pos; pos -= lowbit(pos)) {
            res += tree[pos];
        }
        return res;
    }
}

namespace unionSet {
    int p[N];

    int find(int x) {
        if (p[x] != x) return p[x] = find(p[x]);
        return p[x];
    }

    inline void uion(int a, int b) {
        int pa = find(a), pb = find(b);
        p[pa] = pb;
    }
}

namespace suffixTree {
    int son[N][26], cnt[N], idx;

    void insert(string &str) {
        int p = 0;
        for(const char i : str){
            int u = i - 'a';
            if (!son[p][u]) son[p][u] = ++idx;
            p = son[p][u];
        }
        cnt[p]++;
    }
    
    int query(string& str){
        int p = 0;
        for(const auto ch : str){
            int u = ch - 'a';
            if(!son[p][u]) return 0;
            p = son[p][u];
        }
        return cnt[p];
    }
}