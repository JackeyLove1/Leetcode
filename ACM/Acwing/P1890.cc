#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e6 + 100;
using ll = long long;
int n, m;
int w[N];
struct Node {
    int l, r;
    int v;
} tr[N * 4];

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

void pushup(int u) {
    tr[u].v = gcd(tr[u << 1].v, tr[u << 1 | 1].v);
}

void pushdown(int u) {
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    return;
}

void build(int u, int l, int r) {
    if (l == r) tr[u] = {l, r, w[r]};
    else {
        tr[u] = {l, r, 0};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void modify(int u, int l, int r, int d) {
    if (tr[u].l >= l && tr[u].r <= r) {
        return;
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
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].v;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    int sum = 0;
    if (l <= mid) sum = gcd(query(u << 1, l, r), 0);
    if (r > mid) sum = gcd(query(u << 1 | 1, l, r), sum);
    return sum;
}


int main() {
    fhj();
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> w[i];
    build(1, 1, n);
    int l, r;
    while (m--) {
        cin >> l >> r;
        cout << query(1, l, r) << endl;
    }
    return 0;
}


