#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 210, M = 5200 * 2 + 10, INF = 1e8;

int n, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];
bool st[N];

void add(int a, int b, int c)
{
    e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx ++ ;
}

bool bfs()
{
    int hh = 0, tt = 0;
    memset(d, -1, sizeof d);
    q[0] = S, d[S] = 0, cur[S] = h[S];
    while (hh <= tt)
    {
        int t = q[hh ++ ];
        for (int i = h[t]; ~i; i = ne[i])
        {
            int ver = e[i];
            if (d[ver] == -1 && f[i])
            {
                d[ver] = d[t] + 1;
                cur[ver] = h[ver];
                if (ver == T) return true;
                q[ ++ tt] = ver;
            }
        }
    }
    return false;
}

int find(int u, int limit)
{
    if (u == T) return limit;
    int flow = 0;
    for (int i = cur[u]; ~i && flow < limit; i = ne[i])
    {
        cur[u] = i;
        int ver = e[i];
        if (d[ver] == d[u] + 1 && f[i])
        {
            int t = find(ver, min(f[i], limit - flow));
            if (!t) d[ver] = -1;
            f[i] -= t, f[i ^ 1] += t, flow += t;
        }
    }
    return flow;
}

int dinic()
{
    int r = 0, flow;
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r;
}

void dfs(int u)
{
    st[u] = true;
    for (int i = h[u]; ~i; i = ne[i])
        if (f[i] && !st[e[i]])
            dfs(e[i]);
}

int main()
{
    scanf("%d%d", &n, &m);
    S = 0, T = n * 2 + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i ++ )
    {
        int w;
        scanf("%d",  &w);
        add(S, i, w);
    }
    for (int i = 1; i <= n; i ++ )
    {
        int w;
        scanf("%d", &w);
        add(n + i, T, w);
    }

    while (m -- )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(b, n + a, INF);
    }

    printf("%d\n", dinic());
    dfs(S);

    int cnt = 0;
    for (int i = 0; i < idx; i += 2)
    {
        int a = e[i ^ 1], b = e[i];
        if (st[a] && !st[b]) cnt ++ ;
    }

    printf("%d\n", cnt);
    for (int i = 0; i < idx; i += 2)
    {
        int a = e[i ^ 1], b = e[i];
        if (st[a] && !st[b])
        {
            if (a == S) printf("%d +\n", b);
        }
    }
    for (int i = 0; i < idx; i += 2)
    {
        int a = e[i ^ 1], b = e[i];
        if (st[a] && !st[b])
        {
            if (b == T) printf("%d -\n", a - n);
        }
    }

    return 0;
}