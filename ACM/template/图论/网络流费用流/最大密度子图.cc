#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110, M = (1000 + N * 2) * 2, INF = 1e8;

int n, m, S, T;
int h[N], e[M], ne[M], idx;
double f[M];
int q[N], d[N], cur[N];
int dg[N];

struct Edge
{
    int a, b;
}edges[M];

int ans;
bool st[N];

void add(int a, int b, double c1, double c2)
{
    e[idx] = b, f[idx] = c1, ne[idx] = h[a], h[a] = idx ++ ;
    e[idx] = a, f[idx] = c2, ne[idx] = h[b], h[b] = idx ++ ;
}

void build(double g)
{
    memset(h, -1, sizeof h);
    idx = 0;
    for (int i = 0; i < m; i ++ ) add(edges[i].a, edges[i].b, 1, 1);
    for (int i = 1; i <= n; i ++ )
    {
        add(S, i, m, 0);
        add(i, T, m + g * 2 - dg[i], 0);
    }
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
            if (d[ver] == -1 && f[i] > 0)
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

double find(int u, double limit)
{
    if (u == T) return limit;
    double flow = 0;
    for (int i = cur[u]; ~i && flow < limit; i = ne[i])
    {
        cur[u] = i;
        int ver = e[i];
        if (d[ver] == d[u] + 1 && f[i] > 0)
        {
            double t = find(ver, min(f[i], limit - flow));
            if (t <= 0) d[ver] = -1;
            f[i] -= t, f[i ^ 1] += t, flow += t;
        }
    }
    return flow;
}

double dinic(double g)
{
    build(g);
    double r = 0, flow;
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r;
}

void dfs(int u)
{
    st[u] = true;
    if (u != S) ans ++ ;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int ver = e[i];
        if (!st[ver] && f[i] > 0)
            dfs(ver);
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    S = 0, T = n + 1;

    for (int i = 0; i < m; i ++ )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        dg[a] ++, dg[b] ++ ;
        edges[i] = {a, b};
    }

    double l = 0, r = m;
    while (r - l > 1e-8)
    {
        double mid = (l + r) / 2;
        double t = dinic(mid);
        if (m * n - t > 0) l = mid;
        else r = mid;
    }

    dinic(l);
    dfs(S);

    if (!ans) puts("1\n1");
    else
    {
        printf("%d\n", ans);
        for (int i = 1; i <= n; i ++ )
            if (st[i])
                printf("%d\n", i);
    }
    return 0;
}