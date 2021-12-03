#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <string>
#include <map>
#include <stack>
#include <vector>
#include <set>
#include <queue>
//#pragma comment (linker,"/STACK:102400000,102400000")
#define maxn 205
#define MAXN 100005
#define mod 1000000000
#define INF 0x3f3f3f3f
using namespace std;
 
int n,m,ans,k,cnt,est;
int dp[1<<14][14];
int u[14],v[14];
int id[maxn][maxn],dist[14][14];
bool vis[maxn][maxn];
int mp[maxn][maxn];
int dx[]={-1,1,0,0};
int dy[]={0,0,-1,1};
struct Node
{
    int x,y,step;
    bool operator <(const Node&x1) const
    {
        return step>x1.step;
    }
}cur,now;
priority_queue<Node>q;
 
void bfs(int bx,int by,int xx)
{
    int i,j,nx,ny,tx,ty,flag=0;
    memset(vis,0,sizeof(vis));
    while(!q.empty()) q.pop();
    cur.x=bx;
    cur.y=by;
    cur.step=0;
    vis[bx][by]=1;
    q.push(cur);
    while(!q.empty())
    {
        now=q.top();
        q.pop();
        nx=now.x;
        ny=now.y;
        if(id[nx][ny]!=-1) dist[xx][id[nx][ny]]=now.step;
        for(i=0;i<4;i++)
        {
            tx=nx+dx[i];
            ty=ny+dy[i];
            if(tx<1||tx>n||ty<1||ty>m)
            {
                if(!flag) flag=1,dp[1<<xx][xx]=now.step+mp[u[xx]][v[xx]];
                continue ;
            }
            if(vis[tx][ty]||mp[tx][ty]==-1) continue ;
            cur.x=tx;
            cur.y=ty;
            cur.step=now.step+mp[tx][ty];
            vis[tx][ty]=1;
            q.push(cur);
        }
    }
}
void solve()
{
    int i,j,p,ma,st;
    ma=1<<k;
    for(i=0;i<ma;i++)
    {
        for(j=0;j<k;j++)
        {
            if(dp[i][j]>=INF) continue ;
            for(p=0;p<k;p++)
            {
                if(p==j||(i&(1<<p))) continue ;
                st=i|(1<<p);
                dp[st][p]=min(dp[st][p],dp[i][j]+dist[j][p]);
            }
        }
    }
    ans=INF;
    for(i=0;i<k;i++)
    {
        ans=min(ans,dp[est][i]+dp[1<<i][i]-mp[u[i]][v[i]]);
    }
    if(ans>=INF) ans=0;
}
int main()
{
    int i,j,t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=m;j++)
            {
                scanf("%d",&mp[i][j]);
            }
        }
        memset(id,-1,sizeof(id));
        memset(dp,0x3f,sizeof(dp));
        scanf("%d",&k);
        for(i=0;i<k;i++)
        {
            scanf("%d%d",&u[i],&v[i]);
            u[i]++,v[i]++;
            id[u[i]][v[i]]=i;
        }
        est=(1<<k)-1;
        for(i=0;i<k;i++)
        {
            if(mp[u[i]][v[i]]==-1)  // 汗 去掉也能A
            {
                est=est&(~(1<<i));
                continue ;
            }
            bfs(u[i],v[i],i);
            if(dp[1<<i][i]==INF) est=est&(~(1<<i));  // 汗 去掉也能A  没有设track
        }
        solve();
        printf("%d\n",ans);
    }
    return 0;
}