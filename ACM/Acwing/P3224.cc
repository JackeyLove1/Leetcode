#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1800010;

int n, m;
struct Node
{
    int s[2], p, v, id;
    int size;

    void init(int _v, int _id, int _p)
    {
        v = _v, id = _id, p = _p;
        size = 1;
    }
}tr[N];
int root[N], idx;
int p[N];

int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

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

void splay(int x, int k, int b)
{
    while (tr[x].p != k)
    {
        int y = tr[x].p, z = tr[y].p;
        if (z != k)
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
    if (!k) root[b] = x;
}

void insert(int v, int id, int b)
{
    int u = root[b], p = 0;
    while (u) p = u, u = tr[u].s[v > tr[u].v];
    u = ++ idx;
    if (p) tr[p].s[v > tr[p].v] = u;
    tr[u].init(v, id, p);
    splay(u, 0, b);
}

int get_k(int k, int b)
{
    int u = root[b];
    while (u)
    {
        if (tr[tr[u].s[0]].size >= k) u = tr[u].s[0];
        else if (tr[tr[u].s[0]].size + 1 == k) return tr[u].id;
        else k -= tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
    }
    return -1;
}

void dfs(int u, int b)
{
    if (tr[u].s[0]) dfs(tr[u].s[0], b);
    if (tr[u].s[1]) dfs(tr[u].s[1], b);
    insert(tr[u].v, tr[u].id, b);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ )
    {
        p[i] = root[i] = i;
        int v;
        scanf("%d", &v);
        tr[i].init(v, i, 0);
    }
    idx = n;

    while (m -- )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        a = find(a), b = find(b);
        if (a != b)
        {
            if (tr[root[a]].size > tr[root[b]].size) swap(a, b);
            dfs(root[a], b);
            p[a] = b;
        }
    }

    scanf("%d", &m);
    while (m -- )
    {
        char op[2];
        int a, b;
        scanf("%s%d%d", op, &a, &b);
        if (*op == 'B')
        {
            a = find(a), b = find(b);
            if (a != b)
            {
                if (tr[root[a]].size > tr[root[b]].size) swap(a, b);
                dfs(root[a], b);
                p[a] = b;
            }
        }
        else
        {
            a = find(a);
            if (tr[root[a]].size < b) puts("-1");
            else printf("%d\n", get_k(b, a));
        }
    }

    return 0;
}