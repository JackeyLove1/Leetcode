// practice 2022-11-13
// author: fanhj
#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 100010, M = 300010, INF = 0x3f3f3f3f;
int n, m;
int h[N], e[M], w[M], ne[M], f[N], pre[N], idx;
using ll = long long;
ll dist[N];
int cnt[N], d[N];
bool st[N];

inline void add(int a, int b, int c) {
    e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}

int S, T;

bool bfs() {
    queue<int> q;
    memset(st, false, sizeof st);
    q.push(S), st[S] = true, d[S] = INF;
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        for (int i = h[t]; i != -1; i = ne[i]) {
            int ver = e[i];
            if (!st[ver] && f[i]) {
                st[ver] = true;
                d[ver] = std::min(d[t], f[i]);
                pre[ver] = i;
                if (ver == T) return true;
                q.push(ver);
            }
        }
    }
    return false;
}

int EK() {
    int r = 0;
    while (bfs()) {
        r += d[T];
        for (int i = T; i != S; i = e[pre[i] ^ 1]) {
            f[pre[i]] -= d[T], f[pre[i] ^ 1] += d[T];
        }
    }
    return r;
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d%d%d", &n, &m, &S, &T);
    while (m--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }

    printf("%d\n", EK());

    return 0;
}

// practice 2022-11-13
// author: fanhj
#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 100010, M = 300010, INF = 0x3f3f3f3f;
int n, m;
int h[N], e[M], w[M], ne[M], f[N], pre[N], idx;
using ll = long long;
ll dist[N];
int cnt[N], d[N], cur[N];
bool st[N];

inline void add(int a, int b, int c) {
    e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}

int S, T;

bool bfs() {
    queue<int> q;
    memset(st, false, sizeof st);
    memset(d, -1, sizeof d);
    q.push(S), st[S] = true, d[S] = 0, cur[S] = h[S];
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        for (int i = h[t]; i != -1; i = ne[i]) {
            int ver = e[i];
            if (d[ver] == -1 && f[i]) {
                d[ver] = d[t] + 1;
                cur[ver] = h[ver];
                if (ver == T) return true;
                q.push(ver);
            }
        }
    }
    return false;
}

int find(int u, int limit) {
    if (u == T) return limit;
    int flow = 0;
    for (int i = cur[u]; i != -1 && flow < limit; i = ne[i]) {
        cur[u] = i;
        int ver = e[i];
        if (d[ver] == d[u] + 1 && f[i]) {
            int t = find(ver, std::min(f[i], limit - flow));
            if (!t) d[ver] = -1;
            f[i] -= t, f[i ^ 1] += t, flow += t;
        }
    }
    return flow;
}

int dinic() {
    int r = 0, flow;
    while (bfs()) {
        while (flow = find(S, INF)) r += flow;
    }
    return r;
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d%d%d", &n, &m, &S, &T);
    while (m--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }

    printf("%d\n", dinic());

    return 0;
}

// practice 2022-11-13
// author: fanhj
// splay
#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 500010, M = 65, INF = 0x3f3f3f3f;

int n, m;

struct Node {
    int s[2], p, v;
    int size, rev;

    void init(int _v, int _p) {
        v = _v, p = _p;
        size = 1, rev = 0;
    }
} tr[N];

int root, idx;

void pushup(int x) {
    tr[x].size = tr[tr[x].s[0]].size + tr[tr[x].s[1]].size + 1;
}

void pushdown(int x) {
    if (tr[x].rev) {
        swap(tr[x].s[0], tr[x].s[1]);
        tr[tr[x].s[0]].rev ^= 1;
        tr[tr[x].s[1]].rev ^= 1;
        tr[x].rev = 0;
    }
}

void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;  // k=0表示x是y的左儿子；k=1表示x是y的右儿子
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;// 边1 z原来的儿子y变为x  x的父节点变为z
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;// 边3 y的左儿子变为x的右儿子B,x的右儿子的父节点变为y
    tr[x].s[k ^ 1] = y, tr[y].p = x;// 边2 x的右儿子变为y,y的父节点变为x
    pushup(y), pushup(x);// A,B,C三个点信息没变,但x,y子树信息变了,又y在x下面,所以先维护更新y子树,再维护更新x子树
}

void splay(int x, int k) {
    while (tr[x].p != k) {
        int y = tr[x].p, z = tr[y].p;
        if (z != k)
            // 如果是折线关系  ==  x是y的右/左儿子 且 y是z的左/右儿子  一0一1
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);//折线rotate两次x
            else rotate(y);//直线rotate 一次y一次x
        rotate(x);
    }
    if (!k) root = x;//如果k==0 根节点更新为x
}


int insert(int v) {
    int u = root, p = 0;
    while (u) p = u, u = tr[u].s[v > tr[u].v];
    u = ++idx;
    if (p) tr[p].s[v > tr[p].v] = u;
    tr[u].init(v, p);
    splay(u, 0);
    return u;
}

// get k-th value's pos
int get_k_pos(int k) {
    int u = root;
    while (u) {
        pushdown(u);
        if (tr[tr[u].s[0]].size >= k) u = tr[u].s[0];
        else if (tr[tr[u].s[0]].size + 1 == k) return u;
        else k -= tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
    }
    return -1;
}

// get k-th value
int get_k(int k) {
    int u = root;
    while (u) {
        pushdown(u);
        if (tr[tr[u].s[0]].size >= k) u = tr[u].s[0];
        else if (tr[tr[u].s[0]].size + 1 == k) return tr[u].v;
        else k -= tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
    }
    return -1;
}

int get(int v) {
    int u = root, res;
    while (u) {
        if (tr[u].v >= v) res = u, u = tr[u].s[0];
        else u = tr[u].s[1];
    }
    return res;
}

void output(int u) {
    pushdown(u);
    if (tr[u].s[0]) output(tr[u].s[0]);
    if (tr[u].v >= 1 && tr[u].v <= n) cout << tr[u].v << " ";
    if (tr[u].s[1]) output(tr[u].s[1]);
}

// 翻转[l, r]之间的区间
// 获得l的前驱节点l0和r的后继节点r0
// 然后将l0挂载到0下，将r0挂载到l0下，最后将rev翻转即可
void splay_reverse(int l, int r) {
    auto l0 = get_k_pos(l - 1), r0 = get_k_pos(r + 1);
    splay(l0, 0), splay(r0, l0);
    tr[tr[r0].s[0]].rev ^= 1;
}

inline void solve() {
    cin >> n >> m;
    for (int i = 0; i <= n + 1; ++i) insert(i);
    int l, r;
    while (m--) {
        cin >> l >> r; // 由于又一个0的存在，需要l++,r++
        l++, r++;
        splay_reverse(l, r);
    }
    output(root);
}

int main() {
    fhj();
    solve();
    return 0;
}

