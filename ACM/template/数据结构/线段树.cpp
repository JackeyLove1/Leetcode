#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
using ll = long long;
const int N = 100010;

int n, m;
int w[N];
struct Node
{
    int l, r;
    ll sum, add;
}tr[N * 4];

void pushup(int u)
{
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void pushdown(int u)
{
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    if (root.add)
    {
        left.add += root.add, left.sum += (ll)(left.r - left.l + 1) * root.add;
        right.add += root.add, right.sum += (ll)(right.r - right.l + 1) * root.add;
        root.add = 0;
    }
}

void build(int u, int l, int r)
{
    if (l == r) tr[u] = {l, r, w[r], 0};
    else
    {
        tr[u] = {l, r};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void modify(int u, int l, int r, int d)
{
    if (tr[u].l >= l && tr[u].r <= r)
    {
        tr[u].sum += (ll)(tr[u].r - tr[u].l + 1) * d;
        tr[u].add += d;
    }
    else    // 一定要分裂
    {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, r, d);
        if (r > mid) modify(u << 1 | 1, l, r, d);
        pushup(u);
    }
}

ll query(int u, int l, int r)
{
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].sum;

    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    ll sum = 0;
    if (l <= mid) sum = query(u << 1, l, r);
    if (r > mid) sum += query(u << 1 | 1, l, r);
    return sum;
}


int main()
{
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]);

    build(1, 1, n);

    char op[2];
    int l, r, d;

    while (m -- )
    {
        scanf("%s%d%d", op, &l, &r);
        if (*op == 'C')
        {
            scanf("%d", &d);
            modify(1, l, r, d);
        }
        else printf("%lld\n", query(1, l, r));
    }

    return 0;
}

/*
#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ll = long long;
const int N = 1e5 + 100;

int n, m, p;
int w[N];
struct Node {
    int l, r;
    ll sum, add, mul;
} tr[N * 4];

void pushup(int u) {
    tr[u].sum = (tr[u << 1].sum % p + tr[u << 1 | 1].sum % p) % p;
}

void pushdown(int u) {
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    left.mul = left.mul * root.mul % p;
    right.mul = right.mul * root.mul % p;
    left.sum = left.sum * root.mul % p;
    right.sum = right.sum * root.mul % p;
    left.add = (left.add * root.mul + root.add) % p, left.sum = (left.sum + (left.r - left.l + 1) * root.add) % p;
    right.add = (right.add * root.mul + root.add) % p, right.sum = (right.sum + (right.r - right.l + 1) * root.add) % p;
    root.add = 0, root.mul = 1;
}

void build(int u, int l, int r) {
    if (l == r) tr[u] = {l, r, w[r] % p, 0, 1};
    else {
        tr[u] = {l, r, 0, 0, 1};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void modify_add(int u, int l, int r, int d) {
    if (tr[u].l >= l && tr[u].r <= r) {
        tr[u].sum = (tr[u].sum + (tr[u].r - tr[u].l + 1) * d) % p;
        tr[u].add = (tr[u].add + d) % p;
    } else {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify_add(u << 1, l, r, d);
        if (r > mid) modify_add(u << 1 | 1, l, r, d);
        pushup(u);
    }
}

void modify_mul(int u, int l, int r, int v) {
    if (tr[u].l >= l && tr[u].r <= r) {
        tr[u].sum = tr[u].sum * v % p;
        tr[u].mul = tr[u].mul * v % p;
        tr[u].add = tr[u].add * v % p;
    } else {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify_mul(u << 1, l, r, v);
        if (r > mid) modify_mul(u << 1 | 1, l, r, v);
        pushup(u);
    }
}

ll query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].sum % p;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    ll sum = 0;
    if (l <= mid) sum = query(u << 1, l, r) % p;
    if (r > mid) sum = (sum + query(u << 1 | 1, l, r)) % p;
    return sum;
}


inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}

int main() {
    // fhj();
    // cin >> n >> m >> p;
    n = read(), m = read(), p = read();
    for (int i = 1; i <= n; ++i) w[i] = read();
    build(1, 1, n);
    while (m--) {
        int op, x, y, k;
        cin >> op;
        if (op == 1) {
            // cin >> x >> y >> k;
            x = read(), y = read(), k = read();
            modify_mul(1, x, y, k);
        } else if (op == 2) {
            // cin >> x >> y >> k;
            x = read(), y = read(), k = read();
            modify_add(1, x, y, k);
        } else {
            // cin >> x >> y;
            x = read(), y = read();
            cout << query(1, x, y) << endl;
        }
    }
    return 0;
}


*/