#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 10010, M = 200010, INF = 1e8;

// cur为当前弧
// d为层次图的层次
int n, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];

// 同EK的add
void add(int a, int b, int c)
{
    e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx ++ ;
}

// 判断是否有增广路，如果有就将其建立出来
// 顺便建立分层图
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
                // ver点没有更新
                // ver的层次+1
                d[ver] = d[t] + 1;
                // 弧优化到当前弧
                cur[ver] = h[ver];
                if (ver == T)  return true;
                q[ ++ tt] = ver;
            }
        }
    }
    return false;
}

// 搜索从当前点出发，最多可以流的流量
// dfs搜索
int find(int u, int limit)
{
    if (u == T) return limit;
    int flow = 0;
    // cur[i]代表当前没有满的路径
    // 已经用过且满的路径不需要再搜索了
    // 增加flow<limit是一个显而易见的限制
    for (int i = cur[u]; ~i && flow < limit; i = ne[i])
    {
        // 先记录一下当前搜索的弧
        cur[u] = i;  // 当前弧优化
        int ver = e[i];
        if (d[ver] == d[u] + 1 && f[i]) //当前点是再上一层图的下一层
        {
            int t = find(ver, min(f[i], limit - flow));
            if (!t) d[ver] = -1; // 搜索失败，表示这个点到终点是没有路径的，赋值-1
            // 更新当前容量网络
            f[i] -= t, f[i ^ 1] += t, flow += t;
        }
    }
    return flow;
}

int dinic()
{
    int r = 0, flow;
    // 如果有增广路
    // 就把所有能够建立的增广路都建立出来
    // 再把其叠加起来
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r;
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &S, &T);
    memset(h, -1, sizeof h);
    while (m -- )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }

    printf("%d\n", dinic());

    return 0;
}