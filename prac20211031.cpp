#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>
#include <bitset>
#include <queue>
#include <deque>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

constexpr int N = 1e6 + 100;

int h[N], ne[N], w[N], e[N], idx;
int dist[N];
int n1, n2, m;

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

inline void init() {
    idx = 0;
    memset(h, -1, sizeof h);
    memset(dist, 0x3f, sizeof dist);
}

bool st[N];

void dfs(int u) {
    st[u] = true;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        // function ...
        // process(j)
        if (!st[j]) dfs(j);
    }
}


void bfs(int u) {
    queue<int> q;
    q.push(u);
    st[u] = true;
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (st[j]) continue;
            // process (j)
            st[j] = true;
            q.push(j);
        }
    }
}

using PII = pair<int, int>;
int n;
constexpr int INF = 0x3f3f3f3f;

inline int dijkstra() {
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    priority_queue<PII, vector<PII>, greater<>> heap;
    heap.push({0, 1}); // dist, point
    while (!heap.size()) {
        auto t = heap.top();
        heap.pop();
        int ver = t.second, dis = t.first;
        if (st[ver]) continue;
        st[ver] = true;
        for (int i = h[ver]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[i] + w[i]) {
                dist[j] = dist[i] + w[i];
                heap.push({dist[j], j});
            }
        }
    }
    return dist[n];
}

int spfa() {
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    dist[1] = 0;
    queue<int> q;
    q.push(1);
    st[1] = true;
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        st[t] = false;
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i], dis = w[i]; // dis: the distance from t to j
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                if (!st[j]) {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
    return dist[n];
}

int g[N][N], d[N][N];

void floyed() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j) d[i][j] = 0;
            else d[i][j] = INF;
        }
    }
    // input i -> j the g[i][j]
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}

// 不断加入临近顶点里权重最小的边(本质上是加入点的过程)
inline int prim() {
    memset(dist, 0x3f, sizeof dist);
    int res = 0;
    for (int i = 0; i < n; ++i) {
        int t = -1;// 将要加入的点
        for (int j = 1; j <= n; ++j) {
            if (!st[j] && (t == -1 || dist[t] > dist[j])) {
                t = j;
            }
        }
        if (i && dist[t] == INF) return INF; // 不存在
        if (i) res += dist[t];
        st[t] = true;
        for (int j = 1; j <= n; ++j) dist[j] = min(dist[j], g[t][j]);
    }
    return res;
}

// O(m*n)
int match[N];

int find(int x) {
    for (int i = h[x]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!st[j]) {
            st[j] = true;
            if (!match[j] || find(match[j])) {
                match[j] = x;
                return true;
            }
        }
    }
    return false;
}

void Hungarian() {
    int res = 0;
    memset(match, 0, sizeof match);
    for (int i = 1; i <= n1; ++i) {
        memset(st, false, sizeof st);
        if (find(i)) {
            ++res;
        }
    }
}

// simple segment tree
struct Node {
    int l, r;
    int v;
} tr[N * 4];

void build(int u, int l, int r) {
    tr[u] = {l, r};
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
}

int query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].v;
    int mid = l + r >> 1;
    int v = 0;
    if (l <= mid) v = query(u << 1, l, r);
    if (r > mid) v = max(v, query(u << 1 | 1, l, r));
    return v;
}

void modify(int u, int x, int v) {
    if (tr[u].l == tr[u].r) tr[u].v = v;
    else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(u << 1, x, v);
        else modify(u << 1 | 1, x, v);
        tr[u].v = max(tr[u << 1].v, tr[u << 1 | 1].v);
    }
}

// lowbit tree
int tree[N];

inline int lowbit(int x) {
    return x & (-x);
}

inline void add(int x, int k) {
    for (int pos = x; pos <= n; pos += lowbit(x)) {
        tree[pos] += k;
    }
}

inline int query(int x) {
    int sum = 0;
    for (int pos = x; pos; pos -= lowbit(x)) {
        sum += tree[pos];
    }
    return sum;
}

int p[N];

int pfind(int x) {
    if (p[x] != x) p[x] = pfind(p[x]);
    return p[x];
}

inline void pinit() {
    for (int i = 1; i <= n; ++i) {
        p[i] = i;
    }
}

inline void merge(int a, int b) {
    p[pfind(a)] = pfind(b);
}

