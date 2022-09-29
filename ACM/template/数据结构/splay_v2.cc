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
    int size, rev;
    int cnt;

    void init(int _v, int _p) {
        v = _v, p = _p;
        size = 1, rev = 0, cnt = 1;
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

// 查找value对应的pos，当v不存在时为大于v的第一个数的pos
int get_pos(int v) {
    int u = root, pos;
    while (u) {
        if (tr[u].v >= v) pos = u, u = tr[u].s[0];
        else u = tr[u].s[1];
    }
    return pos;
}

// 查找一个数的排名
// 找到要查的数字后,直接将它旋转到根,此时它左子树的size+1就是它的排名.
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

// get k-th value
// 查找第k小的数字
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

// 翻转[l, r]之间的区间
// 获得l的前驱节点l0和r的后继节点r0
// 然后将l0挂载到0下，将r0挂载到l0下，最后将rev翻转即可
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