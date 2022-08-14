#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1200, M = 4000, INF = 1e8;

int m, n, S, T;
int h[N], e[M], f[M], w[M], ne[M], idx;
int q[N], d[N], pre[N], incf[N];
bool st[N];
int id[40][40], cost[40][40];

void add(int a, int b, int c, int d)
{
    e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx ++ ;
    e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx ++ ;
}

bool spfa()
{
    int hh = 0, tt = 1;
    memset(d, -0x3f, sizeof d);
    memset(incf, 0, sizeof incf);
    q[0] = S, d[S] = 0, incf[S] = INF;
    while (hh != tt)
    {
        int t = q[hh ++ ];
        if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; ~i; i = ne[i])
        {
            int ver = e[i];
            if (f[i] && d[ver] < d[t] + w[i])
            {
                d[ver] = d[t] + w[i];
                pre[ver] = i;
                incf[ver] = min(f[i], incf[t]);
                if (!st[ver])
                {
                    q[tt ++ ] = ver;
                    if (tt == N) tt = 0;
                    st[ver] = true;
                }
            }
        }
    }
    return incf[T] > 0;
}

int EK()
{
    int cost = 0;
    while (spfa())
    {
        int t = incf[T];
        cost += t * d[T];
        for (int i = T; i != S; i = e[pre[i] ^ 1])
        {
            f[pre[i]] -= t;
            f[pre[i] ^ 1] += t;
        }
    }
    return cost;
}

int main()
{
    int cnt = 0;
    scanf("%d%d", &m, &n);
    S = ++ cnt;
    T = ++ cnt;
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= m + i - 1; j ++ )
        {
            scanf("%d", &cost[i][j]);
            id[i][j] = ++ cnt;
        }

    // 规则1
    memset(h, -1, sizeof h), idx = 0;
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= m + i - 1; j ++ )
        {
            add(id[i][j] * 2, id[i][j] * 2 + 1, 1, cost[i][j]);
            if (i == 1) add(S, id[i][j] * 2, 1, 0);
            if (i == n) add(id[i][j] * 2 + 1, T, 1, 0);
            if (i < n)
            {
                add(id[i][j] * 2 + 1, id[i + 1][j] * 2, 1, 0);
                add(id[i][j] * 2 + 1, id[i + 1][j + 1] * 2, 1, 0);
            }
        }
    printf("%d\n", EK());

    // 规则2
    memset(h, -1, sizeof h), idx = 0;
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= m + i - 1; j ++ )
        {
            add(id[i][j] * 2, id[i][j] * 2 + 1, INF, cost[i][j]);
            if (i == 1) add(S, id[i][j] * 2, 1, 0);
            if (i == n) add(id[i][j] * 2 + 1, T, INF, 0);
            if (i < n)
            {
                add(id[i][j] * 2 + 1, id[i + 1][j] * 2, 1, 0);
                add(id[i][j] * 2 + 1, id[i + 1][j + 1] * 2, 1, 0);
            }
        }
    printf("%d\n", EK());

    // 规则3
    memset(h, -1, sizeof h), idx = 0;
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= m + i - 1; j ++ )
        {
            add(id[i][j] * 2, id[i][j] * 2 + 1, INF, cost[i][j]);
            if (i == 1) add(S, id[i][j] * 2, 1, 0);
            if (i == n) add(id[i][j] * 2 + 1, T, INF, 0);
            if (i < n)
            {
                add(id[i][j] * 2 + 1, id[i + 1][j] * 2, INF, 0);
                add(id[i][j] * 2 + 1, id[i + 1][j + 1] * 2, INF, 0);
            }
        }
    printf("%d\n", EK());

    return 0;
}
