#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

inline int read() {
    int ans = 0, sgn = 1;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-')
            sgn *= -1;
        c = getchar();
    }
    while (isdigit(c)) {
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return ans * sgn;
}

constexpr int N = 1e6 + 100;
struct Node {
    int l, r, v;
};
std::array<Node, N << 5> tr{};
std::array<int, N> root{}, A{};
int idx{0};
int n, m;

void pushup(int u) {
    // todo
    auto &root = tr[u], &left = tr[tr[u].l], &right = tr[tr[u].r];
}

int build(int l, int r) {
    int p = ++idx;
    if (l == r) {
        tr[p].v = A[l];
        return p;
    }
    int mid = l + r >> 1;
    tr[p].l = build(l, mid);
    tr[p].r = build(mid + 1, r);
    pushup(p);
    return p;
}


void pushdown() {
    // todo
}

int insert(int p, int l, int r, int k) {
    int q = ++idx;
    tr[q] = tr[p];
    if (l == r) {
        tr[r].v = k;
        return q;
    }
    int mid = l + r >> 1;
    tr[q].l = insert(tr[p].l, l, mid, k);
    tr[q].r = insert(tr[p].r, mid + 1, r, k);
    pushup(q);
    return q;
}

int update(int p, int l, int r, int x, int k) {
    int q = ++idx;
    tr[q] = tr[p];
    if (l == r) {
        tr[q].v = k;
        return q;
    }
    int mid = l + r >> 1;
    if (x <= mid) tr[q].l = update(tr[p].l, l, mid, x, k);
    else tr[q].r = update(tr[p].r, mid + 1, r, x, k);
    pushup(q);
    return q;
}

int query(int p, int l, int r, int x) {
    if (tr[p].l <= l && r <= tr[p].r <= r) return tr[p].v;
    int mid = l + r >> 1;
    if (x <= mid) return query(tr[p].l, l, mid, x);
    else return query(tr[p].r, mid + 1, r, x);
}

int main() {
    n = read(), m = read();
    for (int i = 1; i <= n; ++i)
        A[i] = read();
    root[0] = build(1, n);
    for (int t = 1; t <= m; ++t) {
        int v = read(), o = read();
        if (o == 1) {
            int x = read(), k = read();
            root[t] = update(root[v], 1, n, x, k);
        } else {
            int x = read();
            root[t] = root[v];
            printf("%d\n", query(root[v], 1, n, x));
        }
    }
    return 0;
}