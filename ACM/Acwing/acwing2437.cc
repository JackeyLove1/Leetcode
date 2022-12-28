#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ll = long long;
#define lson tr[u].s[0]
#define rson tr[u].s[1]

constexpr int N = 6e5 + 100, INF = 1e9;

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
    // cout << "u: " << u << " lson:" << lson << " rson:" << rson << endl;
    auto &rt = tr[u], &l = tr[lson], &r = tr[rson];
    rt.size = l.size + r.size + rt.cnt;
    // cout << "u: " << u << " sz:" << rt.size << endl;
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

// 获得第k大的数
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

//  输出
void output(int u) {
    pushdown(u);
    if (tr[u].s[0]) output(tr[u].s[0]);
    if (tr[u].v >= 2 && tr[u].v <= n + 1) cout << tr[u].v - 1<< " ";
    if (tr[u].s[1]) output(tr[u].s[1]);
}

inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}  // 快读

/*
void build(int &u, int l, int r, int p) {
    if (l > r) return;
    int mid = (l + r) >> 1;
    u = mid;
    tr[u].init(w[mid], p);
    if (l < mid) build(tr[u].s[0], l, mid - 1, u);
    if (r > mid) build(tr[u].s[1], mid + 1, r, u);
    pushup(u);
}
*/
int build(int l, int r, int p) {
    int mid = (l + r) >> 1;
    int u = mid;
    tr[u].init(w[mid], p);
    if (l < mid) tr[u].s[0] = build(l, mid - 1, u);
    if (r > mid) tr[u].s[1] = build(mid + 1, r, u);
    // cout << " build u: " << u << " l:" << l << " r:" << r;
    // cout << " lson: " << lson << " rson: " << rson << endl;
    pushup(u);
    return u;
}

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 1; i <= n + 2; ++i) {
        w[i] = i;
    }
    root = build(1, n + 2, 0);
    while (m--) {
        int l, r;
        cin >> l >> r;
        l = kth(l), r = kth(r + 2);
        // cout << "l: " << l << " r:" << r << endl;
        splay(l, 0), splay(r, l);
        tr[tr[r].s[0]].rev ^= 1;
    }
    output(root);
    return 0;
}