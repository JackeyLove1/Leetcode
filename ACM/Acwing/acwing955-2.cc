#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>
#include <numeric>
#include <array>
#include <unordered_map>
#include <unordered_set>

using namespace std;

using ll = long long;
using PII = pair<int, int>;


static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 500010, M = 65, INF = 0x3f3f3f3f;

int n, m;

struct Node {
    int s[2], p, v;
    int cnt;
    int size, rev, same;
    int ls, rs, ms, sum;

    void init(int _v, int _p) {
        v = _v, p = _p;
        s[0] = s[1] = 0;
        size = 1, rev = 0, cnt = 1, same = 0;
        if (v > 0) ls = rs = ms = sum = v;
        else {
            ls = rs = 0;
            sum = ms = v;
        }
    }
} tr[N];

int root, idx;
int nodes[N], w[N], tt;

void pushup(int x) {
    auto &u = tr[x], &left = tr[tr[x].s[0]], &right = tr[tr[x].s[1]];
    u.size = left.size + right.size + 1;
    u.sum = left.sum + u.v + right.sum;
    u.ms = std::max({left.ms, right.ms, left.rs + u.v + right.ls});
    u.ls = std::max({left.ls, left.sum + u.v + right.ls});
    u.rs = std::max({right.rs, left.rs + u.v + right.sum});
}

void pushdown(int x) {
    auto &u = tr[x], &l = tr[tr[x].s[0]], &r = tr[tr[x].s[1]];
    if (u.same) {
        u.same = u.rev = 0;
        if (u.s[0]) l.same = 1, l.v = u.v, l.sum = l.v * l.size;
        if (u.s[1]) r.same = 1, r.v = u.v, r.sum = r.v * r.size;
        if (u.v > 0) {
            l.ls = l.rs = l.sum;
            r.ls = r.rs = r.sum;
        } else {
            l.ls = l.rs = 0;
            r.ls = r.rs = 0;
        }
    }
    if (u.rev) {
        u.rev = 0;
        if (u.s[0]) l.rev ^= 1, std::swap(l.s[0], l.s[1]), swap(l.ls, l.rs);
        if (u.s[1]) r.rev ^= 1, std::swap(r.s[0], r.s[1]), swap(r.ls, r.rs);

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

int insert(int v) {
    int u = root, p = 0;
    while (u) p = u, u = tr[u].s[v > tr[u].v];
    u = ++idx;
    if (p) tr[p].s[v > tr[p].v] = u;
    tr[u].init(v, p);
    splay(u, 0);
    return u;
}

int build(int l, int r, int p) {
    int mid = l + r >> 1;
    int u = nodes[tt--];
    tr[u].init(w[mid], p);
    if (l < mid) tr[u].s[0] = build(l, mid - 1, u);
    if (r > mid) tr[u].s[1] = build(mid + 1, r, u);
    return u;
}

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

int get_k(int k) {
    return get_k_pos(k);
}

int get_pos(int v) {
    int u = root, pos;
    while (u) {
        if (tr[u].v >= v) pos = u, u = tr[u].s[0];
        else u = tr[u].s[1];
    }
    return pos;
}

int get_rank(int v) {
    auto pos = get_pos(v);
    splay(pos, 0);
    return tr[tr[root].s[0]].size + 1;
}

void output(int u) {
    pushdown(u);
    if (tr[u].s[0]) output(tr[u].s[0]);
    // if (tr[u].v >= 1 && tr[u].v <= n) cout << tr[u].v << " ";
    cout << tr[u].v << " ";
    if (tr[u].s[1]) output(tr[u].s[1]);
}


int get_k_value(int k) {
    int u = root;
    while (u) {
        pushdown(u);
        if (tr[tr[u].s[0]].size >= k) u = tr[u].s[0];
        else if (tr[tr[u].s[0]].size + 1 == k) return tr[u].v;
        else k -= tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
    }
    return -1;
}

void splay_reverse(int l, int r) {
    auto l0 = get_k_pos(l - 1), r0 = get_k_pos(r + 1);
    splay(l0, 0), splay(r0, l0);
    tr[tr[r0].s[0]].rev ^= 1;
}

inline void splay_init() {
    insert(-INF), insert(INF);
}

inline int get_prev_v(int v) {
    auto rk = get_rank(v);
    return get_k_value(rk - 1);
}

inline int get_next_v(int v) {
    auto rk = get_rank(v);
    return get_k_value(rk + 1);
}

inline void del_v(int v) {
    auto rk = get_rank(v);
    auto left = get_k_pos(rk - 1);
    auto right = get_k_pos(rk + 1);
    splay(left, 0), splay(right, left);
    tr[right].s[0] = 0;
}

inline void solve() {

}

int main() {
    splay_init();
    solve();
    return 0;
}