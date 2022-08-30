#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 200010;

int n;
int v[N], dist[N], l[N], r[N], idx;
int p[N];

bool cmp(int x, int y)
{
    if (v[x] != v[y]) return v[x] < v[y];
    return x < y;
}

int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int merge(int x, int y)
{
    if (!x || !y) return x + y;
    if (cmp(y, x)) swap(x, y);
    r[x] = merge(r[x], y);
    if (dist[r[x]] > dist[l[x]]) swap(l[x], r[x]);
    dist[x] = dist[r[x]] + 1;
    return x;
}

int main()
{
    scanf("%d", &n);
    v[0] = 2e9;
    while (n -- )
    {
        int t, x, y;
        scanf("%d%d", &t, &x);
        if (t == 1)
        {
            v[ ++ idx] = x;
            dist[idx] = 1;
            p[idx] = idx;
        }
        else if (t == 2)
        {
            scanf("%d", &y);
            x = find(x), y = find(y);
            if (x != y)
            {
                if (cmp(y, x)) swap(x, y);
                p[y] = x;
                merge(x, y);
            }
        }
        else if (t == 3)
        {
            printf("%d\n", v[find(x)]);
        }
        else
        {
            x = find(x);
            if (cmp(r[x], l[x])) swap(l[x], r[x]);
            p[x] = l[x], p[l[x]] = l[x];
            merge(l[x], r[x]);
        }
    }

    return 0;
}