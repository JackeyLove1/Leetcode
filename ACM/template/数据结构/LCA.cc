#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 40010, M = N * 2;

int n, m;
int h[N], e[M], ne[M], idx;
int depth[N], fa[N][16];
int q[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void bfs(int root)
{
    memset(depth, 0x3f, sizeof depth);
    depth[0] = 0, depth[root] = 1;
    int hh = 0, tt = 0;
    q[0] = root;
    while (hh <= tt)
    {
        int t = q[hh ++ ];
        for (int i = h[t]; ~i; i = ne[i])
        {
            int j = e[i];
            if (depth[j] > depth[t] + 1)
            {
                depth[j] = depth[t] + 1;
                q[ ++ tt] = j;
                fa[j][0] = t;
                for (int k = 1; k <= 15; k ++ )
                    fa[j][k] = fa[fa[j][k - 1]][k - 1];
            }
        }
    }
}

int lca(int a, int b)
{
    if (depth[a] < depth[b]) swap(a, b);
    for (int k = 15; k >= 0; k -- )
        if (depth[fa[a][k]] >= depth[b])
            a = fa[a][k];
    if (a == b) return a;
    for (int k = 15; k >= 0; k -- )
        if (fa[a][k] != fa[b][k])
        {
            a = fa[a][k];
            b = fa[b][k];
        }
    return fa[a][0];
}

/*
void dfs(int node)
{
    vis[node]=true;
    for(int i=head[node]; i; i=edge2[i].next){ //前向星遍历 
        int to=edge2[i].to;
        if(vis[to]) continue;
        deep[to]=deep[node]+1; //计算深度 
        fa[to][0]=node; //储存父节点 
        w[to][0]=edge2[i].w; //储存到父节点的权值 
        dfs(to);
    }
    return ;
}

int lca(int x, int y)
{
    if(find(x)!=find(y)) return -1; //不连通，输出-1 
    int ans=INF;
    if(deep[x]>deep[y]) swap(x,y); //保证y节点更深 
    //将y节点上提到于x节点相同深度 
    for(int i=20; i>=0; i--)
        if(deep[fa[y][i]]>=deep[x]){
            ans=min(ans, w[y][i]);  //更新最大载重（最小边权） 
            y=fa[y][i]; //修改y位置 
        }
    if(x==y) return ans; //如果位置已经相等，直接返回答案 
    //寻找公共祖先 
    for(int i=20; i>=0; i--)
        if(fa[x][i]!=fa[y][i]){
            ans=min(ans, min(w[x][i], w[y][i])); //更新最大载重（最小边权）
            x=fa[x][i]; 
            y=fa[y][i]; //修改x,y位置 
        }
    ans=min(ans, min(w[x][0], w[y][0]));
    //更新此时x,y到公共祖先最大载重，fa[x][0], fa[y][0]即为公共祖先 
    return ans;
}
kruskal();
    for(int i=1; i<=n; i++)
        if(!vis[i]){ //dfs收集信息 
            deep[i]=1; 
            dfs(i);
            fa[i][0]=i;
            w[i][0]=INF;
        }
    //LCA初始化 
    for(int i=1; i<=20; i++)
        for(int j=1; j<=n; j++){
            fa[j][i]=fa[fa[j][i-1]][i-1]; 
            w[j][i]=min(w[j][i-1], w[fa[j][i-1]][i-1]);
        }
*/
int main()
{
    scanf("%d", &n);
    int root = 0;
    memset(h, -1, sizeof h);

    for (int i = 0; i < n; i ++ )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        if (b == -1) root = a;
        else add(a, b), add(b, a);
    }

    bfs(root);

    scanf("%d", &m);
    while (m -- )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        int p = lca(a, b);
        if (p == a) puts("1");
        else if (p == b) puts("2");
        else puts("0");
    }

    return 0;
}