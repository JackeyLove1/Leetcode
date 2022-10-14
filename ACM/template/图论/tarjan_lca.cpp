#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 10010, M = N * 2;

int n, m;
int h[N], e[M], w[M], ne[M], idx;
int dist[N];
int p[N];
int res[M];
int st[N];
vector<PII> query[N];   // first存查询的另外一个点，second存查询编号

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int u, int fa)
{
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j == fa) continue;
        dist[j] = dist[u] + w[i];
        dfs(j, u);
    }
}

int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void tarjan(int u)
{
    st[u] = 1;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (!st[j])
        {
            tarjan(j);
            p[j] = u;
        }
    }

    for (auto item : query[u])
    {
        int y = item.first, id = item.second;
        if (st[y] == 2)
        {
            int anc = find(y);
            res[id] = dist[u] + dist[y] - dist[anc] * 2;
        }
    }

    st[u] = 2;
}

int main()
{
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i ++ )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
    }

    for (int i = 0; i < m; i ++ )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        if (a != b)
        {
            query[a].push_back({b, i});
            query[b].push_back({a, i});
        }
    }

    for (int i = 1; i <= n; i ++ ) p[i] = i;

    dfs(1, -1);
    tarjan(1);

    for (int i = 0; i < m; i ++ ) printf("%d\n", res[i]);

    return 0;
}
