#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>
using namespace std;
const int INF=0x3f3f3f3f;
const int maxn=1e3+10;
const int maxm=1e4+10;
const int maxc=100+10;

int n,m,q;
int p[maxn];

struct Edge{
    int u,v,w;
    Edge(int _u=0,int _v=0,int _w=0){u=_u,v=_v,w=_w;}
};
vector<Edge> E;
vector<int> G[maxn];
void init(int l,int r)
{
    E.clear();
    for(int i=l;i<=r;i++) G[i].clear();
}
void addedge(int u,int v,int w)
{
    E.push_back(Edge(u,v,w));
    G[u].push_back(E.size()-1);
}

struct Qnode{
    int v;
    int d,r;
    Qnode(){}
    Qnode(int _v,int _d,int _r) {
        v=_v, d=_d, r=_r;
    }
    bool operator<(const Qnode& oth)const {
        return d>oth.d;
    }
};
int d[maxn][maxc],vis[maxn][maxc];
int dijkstra(int c,int s,int t)
{
    memset(d,0x3f,sizeof(d));
    memset(vis,0,sizeof(vis));

    priority_queue<Qnode> Q;
    d[s][0]=0, Q.push(Qnode(s,d[s][0],0));
    while(!Q.empty())
    {
        int u=Q.top().v, r=Q.top().r; Q.pop();
        if(u==t) return d[u][r];
        if(vis[u][r]) continue;
        else vis[u][r]=1;

        if(r<c) {
            d[u][r+1]=d[u][r]+p[u], Q.push(Qnode(u,d[u][r+1],r+1));
        }
        for(int i=0;i<G[u].size();i++)
        {
            Edge &e=E[G[u][i]]; int v=e.v;
            if(r<e.w || vis[v][r-e.w]) continue;
            if(d[v][r-e.w]>d[u][r]) {
                d[v][r-e.w]=d[u][r], Q.push(Qnode(v,d[v][r-e.w],r-e.w));
            }
        }
    }
    return INF;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++) scanf("%d",&p[i]);
    init(1,n);
    for(int i=1,u,v,w;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        addedge(u,v,w);
        addedge(v,u,w);
    }
    scanf("%d",&q);
    for(int i=1,c,s,t;i<=q;i++)
    {
        scanf("%d%d%d",&c,&s,&t);
        int ans=dijkstra(c,s,t);
        if(ans<INF) printf("%d\n",ans);
        else printf("impossible\n");
    }
}