#include <bits/stdc++.h>
using namespace std;
struct edge { int to, cost; };
typedef pair<int, int> P; // first是最短距离，second是顶点的编号 

const int MAX_V = 2000005;
int n, m, s, t, k;
int d[MAX_V];
vector<edge> G[MAX_V];

void dijkstra()
{
    priority_queue<P, vector<P>, greater<P> >que;
    memset(d, 0x3f, sizeof(d));
    d[s] = 0;
    que.push(P(0, s));
    
    while (!que.empty()) {
        P p = que.top(); que.pop();
        int v = p.second;
        if (d[v] < p.first) continue;
        for (int i = 0; i < G[v].size(); i++) {
            edge e = G[v][i];
            if (d[e.to] > d[v] + e.cost) {
                d[e.to] = d[v] + e.cost;
                que.push(P(d[e.to], e.to));
            }
        }
    }
}

int main()
{
    scanf("%d%d%d%d%d", &n, &m, &s, &t, &k);
    for(int i = 1; i <= m; i++) {
        int u, v, cost;
        scanf("%d%d%d", &u, &v, &cost);
        for(int j = 0; j <= k; j++) {
            G[u+n*j].push_back({v+n*j,cost});
            G[v+n*j].push_back({u+n*j,cost});
            if(j < k) {
                G[u+n*j].push_back({v+n*(j+1),0});
                G[v+n*j].push_back({u+n*(j+1),0});
            }
        }
    }

    dijkstra();
    int ans=0x3f3f3f3f;
    for(int i = 0; i <= k; i++) ans=min(ans, dis[t+n*i]);
    printf("%d\n", ans);
}
