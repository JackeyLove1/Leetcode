#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 2000010, INF = 1e9;

int n, m;
struct Node
{
    int s[2], p, v;
    int size;

    void init(int _v, int _p)
    {
        v = _v, p = _p;
        size = 1;
    }
}tr[N];
int L[N], R[N], T[N], idx;
int w[N];

void pushup(int x)
{
    tr[x].size = tr[tr[x].s[0]].size + tr[tr[x].s[1]].size + 1;
}

void rotate(int x)
{
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}

void splay(int& root, int x, int k)
{
    while (tr[x].p != k)
    {
        int y = tr[x].p, z = tr[y].p;
        if (z != k)
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
    if (!k) root = x;
}

void insert(int& root, int v)
{
    int u = root, p = 0;
    while (u) p = u, u = tr[u].s[v > tr[u].v];
    u = ++ idx;
    if (p) tr[p].s[v > tr[p].v] = u;
    tr[u].init(v, p);
    splay(root, u, 0);
}

int get_k(int root, int v)
{
    int u = root, res = 0;
    while (u)
    {
        if (tr[u].v < v) res += tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
        else u = tr[u].s[0];
    }
    return res;
}

void update(int& root, int x, int y)
{
    int u = root;
    while (u)
    {
        if (tr[u].v == x) break;
        if (tr[u].v < x) u = tr[u].s[1];
        else u = tr[u].s[0];
    }
    splay(root, u, 0);
    int l = tr[u].s[0], r = tr[u].s[1];
    while (tr[l].s[1]) l = tr[l].s[1];
    while (tr[r].s[0]) r = tr[r].s[0];
    splay(root, l, 0), splay(root, r, l);
    tr[r].s[0] = 0;
    pushup(r), pushup(l);
    insert(root, y);
}

void build(int u, int l, int r)
{
    L[u] = l, R[u] = r;
    insert(T[u], -INF), insert(T[u], INF);
    for (int i = l; i <= r; i ++ ) insert(T[u], w[i]);
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}

int query(int u, int a, int b, int x)
{
    if (L[u] >= a && R[u] <= b) return get_k(T[u], x) - 1;
    int mid = L[u] + R[u] >> 1, res = 0;
    if (a <= mid) res += query(u << 1, a, b, x);
    if (b > mid) res += query(u << 1 | 1, a, b, x);
    return res;
}

void change(int u, int p, int x)
{
    update(T[u], w[p], x);
    if (L[u] == R[u]) return;
    int mid = L[u] + R[u] >> 1;
    if (p <= mid) change(u << 1, p, x);
    else change(u << 1 | 1, p, x);
}

int get_pre(int root, int v)
{
    int u = root, res = -INF;
    while (u)
    {
        if (tr[u].v < v) res = max(res, tr[u].v), u = tr[u].s[1];
        else u = tr[u].s[0];
    }
    return res;
}

int get_suc(int root, int v)
{
    int u = root, res = INF;
    while (u)
    {
        if (tr[u].v > v) res = min(res, tr[u].v), u = tr[u].s[0];
        else u = tr[u].s[1];
    }
    return res;
}

int query_pre(int u, int a, int b, int x)
{
    if (L[u] >= a && R[u] <= b) return get_pre(T[u], x);
    int mid = L[u] + R[u] >> 1, res = -INF;
    if (a <= mid) res = max(res, query_pre(u << 1, a, b, x));
    if (b > mid) res = max(res, query_pre(u << 1 | 1, a, b, x));
    return res;
}

int query_suc(int u, int a, int b, int x)
{
    if (L[u] >= a && R[u] <= b) return get_suc(T[u], x);
    int mid = L[u] + R[u] >> 1, res = INF;
    if (a <= mid) res = min(res, query_suc(u << 1, a, b, x));
    if (b > mid) res = min(res, query_suc(u << 1 | 1, a, b, x));
    return res;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]);
    build(1, 1, n);

    while (m -- )
    {
        int op, a, b, x;
        scanf("%d", &op);
        if (op == 1)
        {
            scanf("%d%d%d", &a, &b, &x);
            printf("%d\n", query(1, a, b, x) + 1);
        }
        else if (op == 2)
        {
            scanf("%d%d%d", &a, &b, &x);
            int l = 0, r = 1e8;
            while (l < r)
            {
                int mid = l + r + 1 >> 1;
                if (query(1, a, b, mid) + 1 <= x) l = mid;
                else r = mid - 1;
            }
            printf("%d\n", r);
        }
        else if (op == 3)
        {
            scanf("%d%d", &a, &x);
            change(1, a, x);
            w[a] = x;
        }
        else if (op == 4)
        {
            scanf("%d%d%d", &a, &b, &x);
            printf("%d\n", query_pre(1, a, b, x));
        }
        else
        {
            scanf("%d%d%d", &a, &b, &x);
            printf("%d\n", query_suc(1, a, b, x));
        }
    }

    return 0;
}
