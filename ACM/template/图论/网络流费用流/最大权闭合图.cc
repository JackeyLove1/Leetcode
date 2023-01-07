#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 55010, M = (50000 * 3 + 5000) * 2 + 10, INF = 1e8;

int n, m, S, T;
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

inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}  // 快读

int main()
{
    scanf("%d%d", &n, &m);
    S = 0, T = n + m + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i ++ )
    {
        int p;
        scanf("%d", &p);
        add(m + i, T, p); // cost
    }

    int tot = 0;
    for (int i = 1; i <= m; i ++ )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(S, i, c); // profit
        add(i, m + a, INF); 
        add(i, m + b, INF);
        tot += c;
    }

    printf("%d\n", tot - dinic());

    return 0;
}

/*
// 输出方案
for (int i = 1; i <= m; i++) if (d[i]) cout << i << ' ';
for (int i = 1; i <= n; i++) if (d[i + m]) cout << i << ' ';
*/