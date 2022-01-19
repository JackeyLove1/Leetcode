#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 510;
int g[N][N];//存储图
int dt[N];//存储各个节点到生成树的距离
int st[N];//节点是否被加入到生成树中
int pre[N];//节点的前去节点
int n, m;//n 个节点，m 条边

void prim()
{
    memset(dt,0x3f, sizeof(dt));//初始化距离数组为一个很大的数（10亿左右）
    int res= 0;
    dt[1] = 0;//从 1 号节点开始生成 
    for(int i = 0; i < n; i++)//每次循环选出一个点加入到生成树
    {
        int t = -1;
        for(int j = 1; j <= n; j++)//每个节点一次判断
        {
            if(!st[j] && (t == -1 || dt[j] < dt[t]))//如果没有在树中，且到树的距离最短，则选择该点
                t = j;
        }

        st[t] = 1;// 选择该点
        res += dt[t];
        for(int i = 1; i <= n; i++)//更新生成树外的点到生成树的距离
        {
            if(dt[i] > g[t][i] && !st[i])//从 t 到节点 i 的距离小于原来距离，则更新。
            {
                dt[i] = g[t][i];//更新距离
                pre[i] = t;//从 t 到 i 的距离更短，i 的前驱变为 t.
            }
        }
    }
}

void getPath()//输出各个边
{
    for(int i = n; i > 1; i--)//n 个节点，所以有 n-1 条边。

    {
        cout << i <<" " << pre[i] << " "<< endl;// i 是节点编号，pre[i] 是 i 节点的前驱节点。他们构成一条边。
    }
}

int main()
{
    memset(g, 0x3f, sizeof(g));//各个点之间的距离初始化成很大的数
    cin >> n >> m;//输入节点数和边数
    while(m --)
    {
        int a, b, w;
        cin >> a >> b >> w;//输出边的两个顶点和权重
        g[a][b] = g[b][a] = min(g[a][b],w);//存储权重
    }

    prim();//求最下生成树
    //getPath();//输出路径
    return 0;
}

/*
const int N=110;
int n;
int w[N][N];
int dist[N];//dist存的是当前连通块和外面的每个点直接相连的边的长度的最小值
bool st[N];//当前这个点是否在连通块内

int prim()
{
    int res = 0;
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    for (int i = 0; i < n; i ++ )//循环n次 每次循环连通块通过最小边加入一个点
    {
        //第2及2次以上的循环 最小边所连的点 也是初始化为-1
        int t = -1;
        for (int j = 1; j <= n; j ++ )
            //j不在连通块内 如果当前还没设置连通块 与外接的最小边(t==-1) || 与j的距离比当前点最小距离的点t还小
            if (!st[j] && (t == -1 || dist[t] > dist[j]))//因为dist[1] = 0 则1肯定作为第一个点加入连通块
                t = j;
        res += dist[t];
        st[t] = true;

        //dist[j] 通过min(dist[j], w[t][j])维护连通块到达每个点的最小距离
        // 假设加进连通块的顺序为 1→2→3
        //t为连通块现在刚加进来的最小点 
        // 在只加进1的时候 dist[j]为所有点到1的距离 dist[j] = w[1][j]
        // t更新为2的时候 dist[j]= min(dist[j], w[t][j])
        //                 则更新为min(w[1][j],w[2][j]);
        // t更新为3的时候 dist[j]= min(dist[j], w[t][j])
        //                 则更新为min(w[1][j],w[2][j],w[3][j]);
        for (int j = 1; j <= n; j ++ ) dist[j] = min(dist[j], w[t][j]);
    }
    return res;
}

*/