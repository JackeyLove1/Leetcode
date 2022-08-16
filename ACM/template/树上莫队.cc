#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

const int N = 100010;

int n, m, len;
int w[N];
int h[N], e[N], ne[N], idx;
int depth[N], f[N][16];
int seq[N], top, first[N], last[N];
int cnt[N], st[N], ans[N];
int que[N];
struct Query
{
    int id, l, r, p;
}q[N];
vector<int> nums;

void add_edge(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int u, int father)
{
    seq[ ++ top] = u;
    first[u] = top;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j != father) dfs(j, u);
    }
    seq[ ++ top] = u;
    last[u] = top;
}

void bfs()
{
    memset(depth, 0x3f, sizeof depth);
    depth[0] = 0, depth[1] = 1;
    int hh = 0, tt = 0;
    que[0] = 1;
    while (hh <= tt)
    {
        int t = que[hh ++ ];
        for (int i = h[t]; ~i; i = ne[i])
        {
            int j = e[i];
            if (depth[j] > depth[t] + 1)
            {
                depth[j] = depth[t] + 1;
                f[j][0] = t;
                for (int k = 1; k <= 15; k ++ )
                    f[j][k] = f[f[j][k - 1]][k - 1];
                que[ ++ tt] = j;
            }
        }
    }
}

int lca(int a, int b)
{
    if (depth[a] < depth[b]) swap(a, b);
    for (int k = 15; k >= 0; k -- )
        if (depth[f[a][k]] >= depth[b])
            a = f[a][k];
    if (a == b) return a;
    for (int k = 15; k >= 0; k -- )
        if (f[a][k] != f[b][k])
        {
            a = f[a][k];
            b = f[b][k];
        }
    return f[a][0];
}

int get(int x)
{
    return x / len;
}

bool cmp(const Query& a, const Query& b)
{
    int i = get(a.l), j = get(b.l);
    if (i != j) return i < j;
    return a.r < b.r;
}

void add(int x, int& res)
{
    st[x] ^= 1;
    if (st[x] == 0)
    {
        cnt[w[x]] -- ;
        if (!cnt[w[x]]) res -- ;
    }
    else
    {
        if (!cnt[w[x]]) res ++ ;
        cnt[w[x]] ++ ;
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]), nums.push_back(w[i]);
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    for (int i = 1; i <= n; i ++ )
        w[i] = lower_bound(nums.begin(), nums.end(), w[i]) - nums.begin();

    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i ++ )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add_edge(a, b), add_edge(b, a);
    }

    dfs(1, -1);
    bfs();

    for (int i = 0; i < m; i ++ )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        if (first[a] > first[b]) swap(a, b);
        int p = lca(a, b);
        if (a == p) q[i] = {i, first[a], first[b]};
        else q[i] = {i, last[a], first[b], p};
    }

    len = sqrt(top);
    sort(q, q + m, cmp);

    for (int i = 0, L = 1, R = 0, res = 0; i < m; i ++ )
    {
        int id = q[i].id, l = q[i].l, r = q[i].r, p = q[i].p;
        while (R < r) add(seq[ ++ R], res);
        while (R > r) add(seq[R -- ], res);
        while (L < l) add(seq[L ++ ], res);
        while (L > l) add(seq[ -- L], res);
        if (p) add(p, res);
        ans[id] = res;
        if (p) add(p, res);
    }

    for (int i = 0; i < m; i ++ ) printf("%d\n", ans[i]);

    return 0;
}
