#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;

constexpr int N = 1e5 + 100, INF = 1e9;

int n, m;

struct Node {
    int s[2], p, v;
    int size, cnt, flag;

    void init(int _v, int _p) {
        v = _v, p = _p;
        size = 1, flag = 0, cnt = 1;
    }
} tr[N];

int root, idx;

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
        int y = tr[u].s[0];
        if (tr[y].size + tr[u].cnt < k) {
            k -= tr[y].size + tr[u].cnt;
            u = tr[u].s[1];
        } else if (tr[y].size >= k) u = y;
        else break;
    }
    splay(u, 0);
    return tr[u].v;
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
    tr[tr[r0].s[0]].flag ^= 1;
}


int main() {
    fhj();
    cin >> n;
    int L = insert(-INF), R = insert(INF);
    while (n--) {
        int op, x;
        cin >> op >> x;
        if (op == 1) {
            insert(x);
        } else if (op == 2) {
            del(x);
        } else if (op == 3) {
            cout << getRank(x) << endl;
        } else if (op == 4) {
            cout << kth(x + 1) << endl;
        } else if (op == 5) {
            cout << tr[getPrev(x)].v << endl;
        } else {
            cout << tr[getNext(x)].v << endl;
        }
    }
    return 0;
}