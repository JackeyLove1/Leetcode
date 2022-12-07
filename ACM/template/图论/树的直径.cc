// 两次DP
/*
树上任意两节点之间最长的简单路径即为树的「直径」
①从任意一点P出发，通过DFS寻找离它最远的点Q。
②再次从点Q出发，通过DFS寻找离它最远的W。
③直径即为WQ。
*/
#include<bits/stdc++.h>
using namespace std;
vector<int>edge[100005];
int vis[100005];
int dis[100005];
void dfs(int st)
{
    for(int i=0;i<edge[st].size();i++)
    {
        int to=edge[st][i];
        if(!vis[to])
        {
            vis[to]=1;
            dis[to]=dis[st]+1;//注意，本代码计算的是无权树的直径，所以边权为1
            //如果是有权树，则这里的1要改为边权
            dfs(to);
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin>>n;//n个点
    for(int i=1;i<=n-1;i++)//因为是树，有n-1条边
    {
        int u,v;
        cin>>u>>v;
        edge[u].push_back(v);
        edge[v].push_back(u);//无向图存储，若是有权树还要用结构体
    }
    dfs(1);//从1出发dfs一边
    int maxlen=0,Q,W,ans=0;
    for(int i=1;i<=n;i++)
    {
        if(dis[i]>maxlen) maxlen=dis[i],Q=i;
        dis[i]=vis[i]=0;
    }//找到直径的一个端点Q
    dfs(Q);//从Q出发
    for(int i=1;i<=n;i++)
        if(dis[i]>ans) ans=dis[i],W=i;//找到另一个端点W，同时得到直径长度
    return 0;
}