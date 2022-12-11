#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> P;

const int MAX_N=1005;
int n, m, s, t, k;
vector<P> G[MAX_N]; //first代表顶点编号，second代表权值
int d[MAX_N][MAX_N];

void dijkstra()
{
    memset(d, 0x3f, sizeof(d));
    d[s][0] = 0;
    priority_queue<P, vector<P>, greater<P> >que; //fisrt代表最短距离，second代表对应层数的顶点编号
    que.push({0,s});
    
    while (!que.empty()) {
        P p = que.front(); que.pop();
        int u = p.second%n, t = p.second/n;
        if (d[u][t]<p.first) continue; //当前取出的最小值不是最短距离，就丢弃这个值 
        for (int i = 0; i < G[u].size(); i++) {
            int v = G[u][i].first, cost = G[u][i].second;
            if(d[v][t]>d[u][t]+cost) d[v][t] = d[u][t]+cost, que.push({d[v][t],t*n+v});
            if(t<k&&d[v][t+1]>d[u][t]) d[v][t+1] = d[u][t], que.push({d[v][t+1],(t+1)*n+v});
        }
    }
}

int main()
{
    scanf("%d%d%d%d%d", &n, &m, &s, &t, &k);
    for(int i=0;i<m;i++) {
        int u, v, cost;
        scanf("%d%d%d", &u, &v, &cost);
        G[u].push_back({v,cost});
        G[v].push_back({u,cost});
    }
    dijkstra();
    int ans=0x3f3f3f3f;
    for(int j = 0; j <= k; j++) 
        ans=min(ans,d[t][j]);
    printf("%d\n",ans);
}