#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ll = long long;
#define lson tr[u].s[0]
#define rson tr[u].s[1]

constexpr int N = 3e5 + 100, INF = 1e9;

int n, m;

struct Node {
    int s[2], p, v;
    int size, cnt, rev, same;
    int sum, ms, ls, rs;

    void init(int _v, int _p) {
        s[0] = s[1] = 0;
        v = _v, p = _p;
        sum = ms = v;
        ls = rs = std::max(v, 0);
        size = 1, same = rev = 0, cnt = 1;
    }
} tr[N];

int root, idx;
vector<int> nodes; // 节点回收站

void pushup(int u) {
    auto &rt = tr[u], &l = tr[lson], &r = tr[rson];
    rt.size = l.size + r.size + 1;
    rt.sum = l.sum + r.sum + rt.v;
    rt.ls = std::max(l.ls, l.sum + rt.v + r.ls);
    rt.rs = std::max(r.rs, r.sum + rt.v + l.rs);
    rt.ms = std::max({l.ms, r.ms, l.rs + rt.v + r.ls});
}

void pushdown(int x) {
    auto &u = tr[x], &l = tr[u.s[0]], &r = tr[u.s[1]];
    if (u.same) {
        u.same = u.rev = 0;
        if (u.s[0]) l.same = 1, l.v = u.v, l.sum = l.v * l.size;
        if (u.s[1]) r.same = 1, r.v = u.v, r.sum = r.v * r.size;
        if (u.v > 0) {
            if (u.s[0]) l.ls = l.ms = l.rs = l.sum;
            if (u.s[1]) r.ls = r.ms = r.rs = r.sum;
        } else {
            if (u.s[0]) l.ls = l.rs = 0, l.ms = l.v;
            if (u.s[1]) r.ls = r.rs = 0, r.ms = r.v;
        }
    }
    if (u.rev) {
        //std::swap(u.s[0], u.s[1]);
        l.rev ^= 1, r.rev ^= 1, u.rev = 0;
        std::swap(l.ls, l.rs), std::swap(r.ls, r.rs);
        std::swap(l.s[0], l.s[1]), std::swap(r.s[0], r.s[1]);
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

void splay(int x, int k) {
    while (tr[x].p != k) {
        int y = tr[x].p, z = tr[y].p;
        if (z != k) {
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
    if (!k) root = x;
}

// 根据序列构造splay
int w[N];

int build(int l, int r, int p) {
    int mid = (l + r) >> 1;
    int u = nodes.back();
    nodes.pop_back();
    tr[u].init(w[mid], p);
    if (l < mid) tr[u].s[0] = build(l, mid - 1, u);
    if (r > mid) tr[u].s[1] = build(mid + 1, r, u);
    pushup(u);
    return u;
}

// dfs回收节点
void dfs(int u) {
    if (u) {
        dfs(tr[u].s[0]);
        dfs(tr[u].s[1]);
        nodes.push_back(u);
    }
}

// 获取值为v的节点然后旋转到根
int makeroot(int v) {
    int u = root;
    while (u && tr[u].s[v > tr[u].v] && v != tr[u].v) {
        // pushdown(u);
        u = tr[u].s[v > tr[u].v];
    }
    splay(u, 0);
    return u;
}

// 获得第k大的数或者得到splay中位置在k的数
int kth(int k) {
    int u = root;
    while (u) {
        pushdown(u);
        if (tr[lson].size >= k) u = lson;
        else if (tr[lson].size + 1 == k) return u;
        else k -= tr[lson].size + 1, u = rson;
    }
    // splay(u, 0);
    // return tr[u].v;
}

// 序列splay的insert
int insert(int pos, int v) {
    int l = kth(pos), r = kth(pos + 1);
    splay(l, 0), splay(r, l);
    int u = nodes.back();
    nodes.pop_back();
    tr[u].init(v, r);
    tr[r].s[0] = u;
    return u;
    // splay(r, 0);
}

// 权值splay的insert
int insert(int v) {
    int u = root, p = 0;
    while (u && tr[u].v != v) p = u, u = tr[u].s[v > tr[u].v];
    if (u) tr[u].cnt++;
    else {
        u = ++idx;
        if (p) tr[p].s[v > tr[p].v] = u;
        tr[u].init(v, p);
    }
    splay(u, 0);
    return u;
}

// 获取值为v的排名
int getRank(int v) {
    makeroot(v);
    return tr[tr[root].s[0]].size;
}

// 获取前驱，严格小于v的节点
int getPrev(int v) {
    makeroot(v);
    int u = root;
    if (tr[u].v < v) return u;
    u = tr[u].s[0];
    while (tr[u].s[1]) u = tr[u].s[1];
    return u;
}

// 获取后继，严格大于v的节点
int getNext(int v) {
    makeroot(v);
    int u = root;
    if (tr[u].v > v) return u;
    u = tr[u].s[1];
    while (tr[u].s[0]) u = tr[u].s[0];
    return u;
}

// 删除v
void del(int v) {
    int pre = getPrev(v);
    int nxt = getNext(v);
    splay(pre, 0), splay(nxt, pre);
    int node = tr[nxt].s[0];
    if (tr[node].cnt > 1) {
        tr[node].cnt--;
        splay(node, 0);
    } else {
        tr[nxt].s[0] = 0;
        splay(nxt, 0);
    }
}

//  输出
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
    // 在有-INF和INF为左右节点的情况下是这样翻转的
    auto l0 = kth(l - 1), r0 = kth(r + 1);
    splay(l0, 0), splay(r0, l0);
    tr[tr[r0].s[0]].rev ^= 1;
}

inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}  // 快读

int main() {
    fhj();
    // std::iota(nodes.begin(), nodes.end(), 1);
    nodes.reserve(N);
    for (int i = 1; i < N; ++i) {
        nodes.push_back(i);
    }
    cin >> n;
    tr[0].ms = w[0] = w[n + 1] = -INF;
    for (int i = 1; i <= n; ++i) cin >> w[i];
    root = build(0, n + 1, 0);
    string op;
    int posi, posj, c;
    cin >> m;
    while (m--) {
        cin >> op;
        // cout << "op: " << op << endl;
        if (op == "I") {
            cin >> posi >> c;
            int u = insert(posi, c);
            splay(u, 0);
        } else if (op == "D") {
            cin >> posi;
            int l = kth(posi), r = kth(posi + 2);
            splay(l, 0), splay(r, l);
            int u = tr[r].s[0];
            dfs(u);
            tr[r].s[0] = 0;
            splay(r, 0);
        } else if (op == "R") {
            cin >> posi >> c;
            int l = kth(posi), r = kth(posi + 2);
            splay(l, 0), splay(r, l);
            auto u = tr[r].s[0];
            tr[u].v = c;
            splay(u, 0);
        } else if (op == "Q") {
            cin >> posi >> posj;
            int l = kth(posi), r = kth(posj + 2);
            splay(l, 0), splay(r, l);
            auto &u = tr[tr[r].s[0]];
            cout << u.ms << endl;
            splay(r, 0);
        }
    }
    return 0;
}