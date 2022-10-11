#include <iostream>
#include <cstring>

using namespace std;

const int N = 1200, M = 3800, INF = 0x3f3f3f3f;

int n, m, S, T;
int h[N], e[M], f[M], w[M], ne[M], idx; //邻接表
int q[N], d[N], pre[N], incf[N]; //EK 算法需要的数组
bool st[N]; //spfa 算法需要的判重数组
int id[40][40], cost[40][40]; //记录每个点的标号和权值

void add(int a, int b, int c, int d) //添加边
{
    e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx++;
}

bool spfa() //判断是否存在最长增广路
{
    int hh = 0, tt = 1;
    q[0] = S;

    memset(d, -0x3f, sizeof d);
    d[S] = 0;

    memset(incf, 0, sizeof incf);
    incf[S] = INF;

    while(hh != tt)
    {
        int t = q[hh++];
        if(hh == N) hh = 0;
        st[t] = false;

        for(int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];

            if(f[i] && d[j] < d[t] + w[i])
            {
                d[j] = d[t] + w[i];
                pre[j] = i;
                incf[j] = min(incf[t], f[i]);

                if(!st[j])
                {
                    q[tt++] = j;
                    if(tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
    return incf[T] > 0;
}

int EK() //EK 算法求最大费用最大流
{
    int cost = 0;
    while(spfa())
    {
        int t = incf[T];
        cost += t * d[T];

        for(int i = T; i != S; i = e[pre[i] ^ 1])
        {
            f[pre[i]] -= t;
            f[pre[i] ^ 1] += t;
        }
    }
    return cost;
}

int main()
{
    scanf("%d%d", &m, &n);

    int cnt = 0; //用于记录唯一编号
    S = ++cnt; //源点
    T = ++cnt; //汇点
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m + i - 1; j++)
        {
            scanf("%d", &cost[i][j]);
            id[i][j] = ++cnt; //给每一个点设置一个唯一编号
            //对于每个点 (i, j)，id[i][j] * 2 表示入点编号，id[i][j] * 2 + 1 表示出点编号
        }

    //规则 1
    memset(h, -1, sizeof h), idx = 0; //初始化邻接表
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m + i - 1; j++)
        {
            add(id[i][j] * 2, id[i][j] * 2 + 1, 1, cost[i][j]); //从每个点的入点向出点连一条边，容量是 1，费用是当前点的权值
            if(i == 1) add(S, id[i][j] * 2, 1, 0); //从源点向所有顶点连一条边，容量是 1，费用是 0
            if(i == n) add(id[i][j] * 2 + 1, T, 1, 0); //从所有底点向汇点连一条边，容量是 1，费用是 0
            if(i < n)
            {
                add(id[i][j] * 2 + 1, id[i + 1][j] * 2, 1, 0); //从当前点向正下方的点连一条边，容量是 1，费用是 0
                add(id[i][j] * 2 + 1, id[i + 1][j + 1] * 2, 1, 0); //从当前点向右下方的点连一条边，容量是 1，费用是 0
            }
        }
    printf("%d\n", EK());

    //规则 2
    memset(h, -1, sizeof h), idx = 0; //初始化邻接表
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m + i - 1; j++)
        {
            add(id[i][j] * 2, id[i][j] * 2 + 1, INF, cost[i][j]); //从每个点的入点向出点连一条边，容量是 INF，费用是当前点的权值
            if(i == 1) add(S, id[i][j] * 2, 1, 0); //从源点向所有顶点连一条边，容量是 1，费用是 0
            if(i == n) add(id[i][j] * 2 + 1, T, INF, 0); //从所有底点向汇点连一条边，容量是 INF，费用是 0
            if(i < n)
            {
                add(id[i][j] * 2 + 1, id[i + 1][j] * 2, 1, 0); //从当前点向正下方的点连一条边，容量是 1，费用是 0
                add(id[i][j] * 2 + 1, id[i + 1][j + 1] * 2, 1, 0); //从当前点向右下方的点连一条边，容量是 1，费用是 0
            }
        }
    printf("%d\n", EK());

    //规则 3
    memset(h, -1, sizeof h), idx = 0; //初始化邻接表
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m + i - 1; j++)
        {
            add(id[i][j] * 2, id[i][j] * 2 + 1, INF, cost[i][j]); //从每个点的入点向出点连一条边，容量是 INF，费用是当前点的权值
            if(i == 1) add(S, id[i][j] * 2, 1, 0); //从源点向所有顶点连一条边，容量是 1，费用是 0
            if(i == n) add(id[i][j] * 2 + 1, T, INF, 0); //从所有底点向汇点连一条边，容量是 INF，费用是 0
            if(i < n)
            {
                add(id[i][j] * 2 + 1, id[i + 1][j] * 2, INF, 0); //从当前点向正下方的点连一条边，容量是 INF，费用是 0
                add(id[i][j] * 2 + 1, id[i + 1][j + 1] * 2, INF, 0); //从当前点向右下方的点连一条边，容量是 INF，费用是 0
            }
        }
    printf("%d\n", EK());

    return 0;
}