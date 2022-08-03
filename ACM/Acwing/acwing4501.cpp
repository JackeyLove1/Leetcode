#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

typedef long long LL;
using ll = long long;
const int N = 100010;

int n, m;
int w[N];
struct Node {
    int l, r;
    ll val, add;
} tr[N * 4];

void pushup(int u) {
    tr[u].val = min(tr[u << 1].val, tr[u << 1 | 1].val);
}

void pushdown(int u) {
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    if (root.add) {
        left.add += root.add, left.val += root.add;
        right.add += root.add, right.val += root.add;
        root.add = 0;
    }
}

void build(int u, int l, int r) {
    if (l == r) tr[u] = {l, r, w[r], 0};
    else {
        tr[u] = {l, r};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void modify(int u, int l, int r, int d) {
    if (tr[u].l >= l && tr[u].r <= r) {
        tr[u].val += d;
        tr[u].add += d;
    } else    // 一定要分裂
    {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, r, d);
        if (r > mid) modify(u << 1 | 1, l, r, d);
        pushup(u);
    }
}

ll query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].val;

    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    ll cnt = 1e6;
    if (l <= mid) cnt = min(cnt, query(u << 1, l, r));
    if (r > mid) cnt = min(cnt, query(u << 1 | 1, l, r));
    return cnt;
}


int main() {
    fhj();
    cin >> n >> m;
    build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        modify(1, x, x, 1);
        if (query(1, 1, n) > 0) {
            cout << 1;
            modify(1, 1, n, -1);
            continue;
        }
        cout << 0;
    }
    return 0;
}

