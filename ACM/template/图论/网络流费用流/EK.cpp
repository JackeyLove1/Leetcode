#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1010, M = 20010, INF = 1e8;

int n, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], pre[N];
bool st[N];

// 数组d表示当前所有边上的容量最小值
// pre前驱节点
// 在残差网络中不断使用BFS寻找增广路，直到找不到
// 就构成了最大流

void add(int a, int b, int c)
{
    e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
    // 残差网络，容量图
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx ++ ;
    // 反向图
}

bool bfs()
{
    int hh = 0, tt = 0;
    memset(st, false, sizeof st);
    q[0] = S, st[S] = true, d[S] = INF;
    while (hh <= tt)
    {
        int t = q[hh ++ ];
        for (int i = h[t]; ~i; i = ne[i])
        {
            int ver = e[i];
            if (!st[ver] && f[i])
            // 如果这个点被遍历过就不需要遍历
            {
                st[ver] = true;
                d[ver] = min(d[t], f[i]);
                // 记录一下前驱边
                pre[ver] = i;
                if (ver == T) return true;
                q[ ++ tt] = ver;
            }
        }
    }
    return false;
}

int EK()
{
    int r = 0;
    while (bfs())
    {
        r += d[T];
        for (int i = T; i != S; i = e[pre[i] ^ 1])
        // 维护容量网络里的残差网络和反图容量
            f[pre[i]] -= d[T], f[pre[i] ^ 1] += d[T];
    }
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

    printf("%d\n", EK());

    return 0;
}

