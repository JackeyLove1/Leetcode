#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 50010, M = (N + 125003) * 2, INF = 2147483647;

int n, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N], A[N];

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
    int s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    S = 0, T = n + 1;
    memset(h, -1, sizeof h);
    while (m -- )
    {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        add(a, b, d - c);
        A[a] -= c, A[b] += c;
    }

    int tot = 0;
    for (int i = 1; i <= n; i ++ )
        if (A[i] > 0) add(S, i, A[i]), tot += A[i];
        else if (A[i] < 0) add(i, T, -A[i]);

    // 最小流
    add(t, s, INF);

    if (dinic() < tot) puts("No Solution");
    else
    {
        int res = f[idx - 1];
        S = t, T = s; // 注意这点
        f[idx - 1] = f[idx - 2] = 0;
        printf("%d\n", res - dinic());
    }

    // 最大流
    add(t, s, INF);
    if (dinic() < tot) puts("No Solution");
    else
    {
        int res = f[idx - 1];
        S = s, T = t;
        f[idx - 1] = f[idx - 2] = 0;
        printf("%d\n", res + dinic());
    }

    return 0;
}