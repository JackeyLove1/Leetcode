#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 10010, M = 30010;

int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int root, ans;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ timestamp;

    int cnt = 0;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
            if (low[j] >= dfn[u]) cnt ++ ; // u为割点
        }
        else low[u] = min(low[u], dfn[j]);
    }

    if (u != root) cnt ++ ;

    ans = max(ans, cnt);
}

int main()
{
    while (scanf("%d%d", &n, &m), n || m)
    {
        memset(dfn, 0, sizeof dfn);
        memset(h, -1, sizeof h);
        idx = timestamp = 0;

        while (m -- )
        {
            int a, b;
            scanf("%d%d", &a, &b);
            add(a, b), add(b, a);
        }

        ans = 0;
        int cnt = 0;
        for (root = 0; root < n; root ++ )
            if (!dfn[root])
            {
                cnt ++ ;
                tarjan(root);
            }

        printf("%d\n", ans + cnt - 1);
    }

    return 0;
}
