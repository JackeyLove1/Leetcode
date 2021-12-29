#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <cstring>
#include <cmath>
#include <list>
#include <atomic>
#include <cstring>
#include <cstdlib>

using namespace std;

template<typename T>
static inline void print(vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class TreeNode {
public:
    int val;
    TreeNode *right, *left;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int val_) : val(val_), left(nullptr), right(nullptr) {}

};

// build a list
static constexpr int N = 1e6 + 100;

int h[N], e[N], w[N], ne[N], idx;

static inline void init() {
    memset(h, -1, sizeof h);
    idx = 0;
}

// add a edge from a to b , weight is c
static inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}


// flag array
bool st[N];

// dfs
void dfs(int u) {
    st[u] = true;
    // i is idx
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!st[j]) dfs(j);
    }
}

// bfs
void bfs(int u) {
    queue<int> q;
    st[u] = true;
    q.push(u);
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (st[j]) continue;
            st[j] = true;
            q.push(j);
        }
    }
}

// topsort
int n;
int d[N], top[N];

bool topsort() {
    int cnt = 0;
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (!d[i]) {
            q.push(i);
            top[cnt++] = i;
        }
    }
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (--d[j] == 0) {
                q.push(j);
                top[cnt++] = j;
            }
        }
    }
    return cnt == n;
}

// dijkstra
static constexpr int INF = 0x3f3f3f3f;
int dist[N]; // distant array
int djkstra() {
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    using PII = pair<int, int>;
    priority_queue<PII, vector<PII>, greater<>> heap;
    heap.push({0, 1}); // distance, point
    while (!heap.empty()) {
        auto t = heap.top();
        heap.pop();
        int ver = t.second, dis = t.first;
        if (st[ver]) continue;
        st[ver] = true;
        for (int i = h[ver]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dis + w[i]) {
                dist[j] = dis + w[i];
                heap.push({dist[j], j});
            }
        }
    }
    if (dist[n] == INF) return INF;
    return dist[n];
}

// floyed
int g[N][N];

void floyed() {
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
}

// prim O(n^2 + m)
int prim() {
    memset(dist, 0x3f, sizeof dist);
    int res = 0;
    for (int i = 0; i < n; ++i) {
        int t = -1;
        for (int j = 1; j <= n; ++j) {
            // 寻找下一个加入集合的节点
            if (!st[j] && (t == -1 || dist[t] > dist[j])) {
                t = j;
            }
        }
        if (i && dist[t] == INF) return INF;
        if (i) res += dist[t];
        st[t] = true;
        // 更新最新距离
        // 这个点距离最新集合的距离
        for (int j = 1; j <= n; ++j) dist[j] = min(dist[j], g[t][j]);
    }
    return res;
}

// segment tree
namespace segment_tree {
    int m, p;
    struct Node {
        int l, r;
        int v;
    } tr[N * 4];

    void pushup(int u) {
        tr[u].v = max(tr[u << 1].v, tr[u << 1 | 1].v);
    }

    void build(int u, int l, int r) {
        tr[u] = {l, r};
        if (l == r) return;
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    }

    void modify(int u, int x, int v) {
        if (tr[u].l == x && tr[u].r == x) tr[u].v = v;
        else {
            int mid = tr[u].l + tr[u].r >> 1;
            if (x <= mid) modify(u << 1, x, v);
            else modify(u << 1 | 1, x, v);
            pushup(u);
        }
    }

    int query(int u, int l, int r) {
        if (tr[u].l >= l && tr[u].r <= r) return tr[u].v;
        int mid = tr[u].l + tr[u].r >> 1;
        int v = 0;
        if (l <= mid) v = query(u << 1, l, r);
        if (r > mid) v = query(u << 1 | 1, l, r);
        return v;
    }
}

namespace lazy_segment_tree {
    // 查询时更新
    using ll = long long;
    int w[N];
    struct Node {
        int l, r;
        ll sum, add;
    } tr[N * 4];

    void pushup(int u) {
        tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
    }

    void pushdown(int u) {
        auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
        if (root.add) {
            left.add += root.add, left.sum += (ll) (left.r - left.l + 1) * root.add;
            right.add += root.add, right.sum += (ll) (right.r - right.l + 1) * root.add;
            root.add = 0;
        }
    }

    void build(int u, int l, int r) {
        if (l == r) tr[u] = {l, r, w[r], 0};
        else {
            tr[u] = {l, r};
            int mid = l + r >> 1;
            build(u << 1, l, mid);
            build(u << 1 | 1, mid + 1, r);
            pushup(u);
        }
    }

    void modify(int u, int l, int r, int d) {
        if (tr[u].l >= l && tr[u].r <= r) {
            tr[u].sum += (ll) (tr[u].r - tr[u].l + 1) * d;
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

namespace tree_array {
    int tree[N];
    int a[N];

    inline int lowbit(int x) {
        return x & (-x);
    }

    inline void add(int x, int k) {
        for (int pos = x; pos <= n; pos += lowbit(pos)) tree[pos] += k;
    }

    inline int query(int x) {
        int sum = 0;
        for (int pos = x; pos; pos -= lowbit(pos)) {
            sum += tree[pos];
        }
        return sum;
    }

    void init() {
        for (int i = 1; i <= n; ++i) {
            tree[i] += a[i];
            int j = i + lowbit(i);
            if (j <= n) tree[j] += tree[i];
        }
    }
}

namespace union_set {
    int p[N];

    int find(int x) {
        if (p[x] != x) p[x] = find(p[x]);
        return p[x];
    }

    inline void init() {
        for (int i = 1; i <= n; ++i) {
            p[i] = i;
        }
    }

    inline void merge(int a, int b) {
        p[find(a)] = find(b);
    }
}

namespace prefix_tree {
    int son[N][26], cnt[N], idx;

    void insert(const string &str) {
        int p = 0;
        for(const char i : str){
            int u = i - 'a';
            if (!son[p][u]) son[p][u] = ++idx;
            p = son[p][u];
        }
        cnt[p]++;
    }
    
    int query(const string& str){
        int p = 0;
        for(const char i : str){
            int u = i - 'a';
            if (!son[p][u]) return 0;
            p = son[p][u];
        }
        return cnt[p];
    }
}

