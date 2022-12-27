#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;
#define ls(x) tr[x].s[0]
#define rs(x) tr[x].s[1]

constexpr int N = 2000010, INF = 1e9;

int n, m;
// union set
int fa[N];

int find(int x) {
    if (x != fa[x]) fa[x] = find(fa[x]);
    return fa[x];
}

inline void merge(int a, int b) {
    a = find(a), b = find(b);
    fa[a] = b;
}

// splay
struct Node {
    int s[2], p, v;
    int size, cnt, flag, id;

    void init(int _v, int _p, int _id) {
        v = _v, p = _p, id = _id;
        size = 1, flag = 0, cnt = 1;
    }
} tr[N];

int root[N], idx;

void pushup(int x) {
    tr[x].size = tr[tr[x].s[0]].size + tr[tr[x].s[1]].size + tr[x].cnt;
}

void pushdown(int x) {
    if (tr[x].flag) {
        swap(tr[x].s[0], tr[x].s[1]);
        tr[tr[x].s[0]].flag ^= 1;
        tr[tr[x].s[1]].flag ^= 1;
        tr[x].flag = 0;
    }
}

void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}

void splay(int x, int k, int b) {
    while (tr[x].p != k) {
        int y = tr[x].p, z = tr[y].p;
        if (z != k) {
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
    if (!k) root[b] = x;
}

// 获取值为v的节点然后旋转到根
int makeroot(int v, int b) {
    int u = root[b];
    while (u && tr[u].s[v > tr[u].v] && v != tr[u].v) {
        // pushdown(u);
        u = tr[u].s[v > tr[u].v];
    }
    splay(u, 0, b);
    return u;
}

int insert(int v, int id, int b) {
    int u = root[b], p = 0;
    while (u && tr[u].v != v) p = u, u = tr[u].s[v > tr[u].v];
    if (u) tr[u].cnt++;
    else {
        u = ++idx;
        if (p) tr[p].s[v > tr[p].v] = u;
        tr[u].init(v, p, id);
    }
    splay(u, 0, b);
    return u;
}

// 获得第k大的数
int kth(int k, int b) {
    int u = root[b];
    while (u) {
        pushdown(u);
        int y = tr[u].s[0];
        if (tr[y].size + tr[u].cnt < k) {
            k -= tr[y].size + tr[u].cnt;
            u = tr[u].s[1];
        } else if (tr[y].size >= k) u = y;
        else break;
    }
    splay(u, 0, b);
    return tr[u].v;
}

// 获取值为v的排名
int getRank(int v, int b) {
    makeroot(v, b);
    return tr[tr[root[b]].s[0]].size;
}

// 获取前驱，严格小于v的节点
int getPrev(int v, int b) {
    makeroot(v, b);
    int u = root[b];
    if (tr[u].v < v) return u;
    u = tr[u].s[0];
    while (tr[u].s[1]) u = tr[u].s[1];
    return u;
}

// 获取后继，严格大于v的节点
int getNext(int v, int b) {
    makeroot(v, b);
    int u = root[b];
    if (tr[u].v > v) return u;
    u = tr[u].s[1];
    while (tr[u].s[0]) u = tr[u].s[0];
    return u;
}

// 删除v
void del(int v, int b) {
    int pre = getPrev(v, b);
    int nxt = getNext(v, b);
    splay(pre, 0, b), splay(nxt, pre, b);
    int node = tr[nxt].s[0];
    if (tr[node].cnt > 1) {
        tr[node].cnt--;
        splay(node, 0, b);
    } else {
        tr[nxt].s[0] = 0;
        splay(nxt, 0, b);
    }
}

//  输出
void output(int u) {
    pushdown(u);
    if (tr[u].s[0]) output(tr[u].s[0]);
    if (tr[u].v >= 1 && tr[u].v <= n) cout << tr[u].v << " ";
    if (tr[u].s[1]) output(tr[u].s[1]);
}

void dfs(int u, int b) {
    if (ls(u)) dfs(ls(u), b);
    if (rs(u)) dfs(rs(u), b);
    insert(tr[u].v, tr[u].id, b);
}

inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}  // 快读

int main() {
    n = read(), m = read();
    for (int i = 1; i <= n; ++i) {
        int v = read();
        fa[i] = i;
        tr[i].init(v, 0, i);
    }
    idx = n;
    while (m--) {
        string op;
        cin >> op;
        if (op == "B") {
            int a = read(), b = read();
            a = find(a), b = find(b);
            if (a != b) {
                if (tr[root[a]].size > tr[root[b]].size) std::swap(a, b);
                dfs(root[a], b);
                merge(a, b);
            }
        } else {
            int a = read(), k = read();
            a = find(a);
            if (tr[root[a]].size < k) cout << -1 << endl;
            else cout << kth(root[a], k) << endl;
        }
    }
    return 0;
}