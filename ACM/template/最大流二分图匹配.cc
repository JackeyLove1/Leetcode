#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110, M = 5210, INF = 1e8;

int m, n, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];

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

int main()
{
    scanf("%d%d", &m, &n);
    S = 0, T = n + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= m; i ++ ) add(S, i, 1);
    for (int i = m + 1; i <= n; i ++ ) add(i, T, 1);

    int a, b;
    while (cin >> a >> b, a != -1) add(a, b, 1);

    printf("%d\n", dinic());
    for (int i = 0; i < idx; i += 2)
        if (e[i] > m && e[i] <= n && !f[i])
            printf("%d %d\n", e[i ^ 1], e[i]);

    return 0;
}
