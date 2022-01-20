#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 100010, M = 600010;

int n, m;
int h[N], hs[N], e[M], ne[M], w[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt, scc_size[N];
int dist[N];

void add(int h[],int a,int b,int c)
{
    e[idx] = b,ne[idx] = h[a],w[idx] = c,h[a] = idx++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = timestamp++;
    stk[++top] = u,in_stk[u] = true;//stk[++top]要和stk[top--]配 而不是stk[top++] stk[0++] = u stk[1++] = t 

    for(int i = h[u];~i;i=ne[i])
    {
        int j = e[i];
        if(!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u],low[j]);
        }
        else if(in_stk[j]) low[u] = min(low[u],dfn[j]);
    }
    if(dfn[u]==low[u])
    {
        scc_cnt++;
        int y;
        do
        {
            y = stk[top--];//忘了强连通分量都是通过dfs后在一个栈里的
            in_stk[y] = false;//漏了
            id[y] = scc_cnt;
            scc_size[scc_cnt]++;
        }while(y!=u);
    }
}

int main()
{
    cin >> n >> m;
    memset(h,-1,sizeof h);
    memset(hs,-1,sizeof h);
    // 超级源点 和i有一个1的边
    for(int i = 1;i<=n;i++)add(h,0,i,1);
    while(m--)
    {
        int t,a,b;
        cin >> t >> a >> b;
        if(t==1)add(h,b,a,0),add(h,a,b,0);
        else if(t==2)add(h,a,b,1);
        else if(t==3)add(h,b,a,0);
        else if(t==4)add(h,b,a,1);
        else add(h,a,b,0);
    }
    tarjan(0);
    bool success = true;
    for(int i=0;i<=n;i++)
    {
        for(int j = h[i];~j;j=ne[j])
        {
            int k = e[j];
            int a = id[i],b = id[k];
            // 如果a和b在一个scc里,判断w[a][b]是否>0
            if(a==b)
            {
                if(w[j]>0)
                {
                    success = false;
                    break;
                }
            }
            // 如果不在一个scc里 在新图里加一条边
            else add(hs,a,b,w[j]);
        }
        if(!success) break;
    }
    if(!success) cout << "-1";
    else
    {
        // 有解 求最长路
        for(int i = scc_cnt;i;i--)
        {
            for(int j = hs[i];~j;j=ne[j])
            {
                int k = e[j];
                dist[k] = max(dist[k],dist[i]+w[j]);
            }
        }
        LL res = 0;
        // 结果 = 新图里每个scc的距离 * scc里的点数 = dist[scc] * cnt[scc] 
        for(int i=1;i<=scc_cnt;i++) res+=(LL)dist[i]*scc_size[i];
        cout << res;
    }
    return 0;
}