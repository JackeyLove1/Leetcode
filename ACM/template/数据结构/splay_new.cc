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
    if (tr[u].v >= 1 && tr[u].v <= n) cout << tr[u].v << " ";
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

// 查找x的前驱
// 查找一个数的前驱/后继
// 为了方便操作,可以先把要查找的值先旋到根.
// 此时如果要查询前驱,前驱一定就是根节点或是在它的左子树中最大的值.
// 那么先比较根节点的权值与要查询的值,如果要查询前驱并且根节点的权值已经比要找前驱的权值要小了,
// 那么根节点就是要查找的前驱.
// 为什么一定是这样的呢?因为find找到一个结点要么找到的是该节点,
// 要么就是与要找的权值最接近的节点.所以根节点的权值与查找的权值最接近.
// 而前驱就是比它权值要小的最大的数,所以根节点就是前驱了.
// 如果根节点不是前驱,那么前驱就是它左子树中的最大值(也就是左子树最右边的节点).
//前驱后继查询写在了同一个函数里,method==0表示查找前驱,method==0表示查找后继
inline int get_prev_or_next_pos(int v, int method) {
    splay(get_rank(v), 0);
    auto u = root;
    if (tr[u].v < v && method == 0) return u;
    if (tr[u].v > v && method == 1) return u;
    u = tr[u].s[method];
    while (tr[u].s[method ^ 1]) {
        u = tr[u].s[method ^ 1];
    }
    return u;
}

// have some problems
int get_prev(int v) {
    return get_prev_or_next_pos(v, 0);
}

// have some problems
int get_next(int v) {
    return get_prev_or_next_pos(v, 1);
}

inline void init() {
    insert(-INF), insert(INF);
}

// need insert value ahead
inline int get_prev_v(int v) {
    auto rk = get_rank(v);
    return get_k_value(rk - 1);
}

// need insert value ahead
inline int get_next_v(int v) {
    auto rk = get_rank(v);
    return get_k_value(rk + 1);
}

// 删除一个数,也是先要确定这个节点的位置.但是删除一个节点不能直接将要删除的节点旋转到根.
// 因为如果旋转到根节点之后它有可能还有左右子树.
// 所以我们可以先找到它的前驱后继,然后将前驱旋到根,后继旋到前驱的下面.此时要删除的点就是后继的左儿子.
// 因为前驱是第一个比它小的数字,所以它在前驱的右边,后继是第一个比它大的数字,所以他在后继的左边,
// 后继旋到了前驱的下面,那么要删除的节点就一定在前驱后继的中间,也就是后继的左儿子
void del(int v) {
    auto left = get_prev(v);
    auto right = get_next(v);
    splay(left, 0), splay(right, left); // 此时v在tr[right].s[0]的位置
    if (tr[tr[right].s[0]].cnt > 1) {
        tr[tr[right].s[0]].cnt--;
        splay(tr[right].s[0], 0);
    } else tr[right].s[0] = 0;
}

// 查询最值
// 查询最值也是通过find函数会找到与一个数最接近的节点的特性,
// 直接find(inf)或者是find(-inf)来找与正无穷最接近的值(最大值)或与负无穷最接近的值(最小值).
int get_max_v() {
    // todo
    return -1;
}

// 将值区间[l, r]删除
void splay_value_delete(int l, int r) {
    // todo
}

int main() {

}