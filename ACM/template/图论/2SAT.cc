#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;

const int N = 2000010, M = 2000010;

int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], ts, stk[N], top;
int id[N], cnt;
bool ins[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ ts;
    stk[ ++ top] = u, ins[u] = true;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        } else if (ins[j]) low[u] = min(low[u], dfn[j]);
    }

    if (low[u] == dfn[u])
    {
        int y;
        cnt ++ ;
        do
        {
            y = stk[top -- ], ins[y] = false, id[y] = cnt;
        } while (y != u);
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);

    while (m -- )
    {
        int i, a, j, b;
        scanf("%d%d%d%d", &i, &a, &j, &b);
        i --, j -- ;
        add(2 * i + !a, 2 * j + b);
        add(2 * j + !b, 2 * i + a);
    }

    for (int i = 0; i < n * 2; i ++ )
        if (!dfn[i])
            tarjan(i);

    for (int i = 0; i < n; i ++ )
        if (id[i * 2] == id[i * 2 + 1])
        {
            puts("IMPOSSIBLE");
            return 0;
        }

    puts("POSSIBLE");
    for (int i = 0; i < n; i ++ )
        if (id[i * 2] < id[i * 2 + 1]) printf("0 ");
        else printf("1 ");

    return 0;
}
