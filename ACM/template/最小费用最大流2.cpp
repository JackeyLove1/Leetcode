#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;
typedef long long ll;

namespace dinic{//MCMF

    const int N = 1e3 + 7, M = 2e4 + 7;
    const ll INF = 0x3f3f3f3f3f;//!因为是long long 所以是五个3f
    int n, S, T;
    int head[N], ver[M], nex[M], tot, cur[N];
    ll dist[N], edge[M], cost[M], maxflow, mincost;
    bool vis[N];

    inline void add(int x, int y, ll z, ll c, bool o = 1){
        ver[tot] = y;
        edge[tot] = z;
        cost[tot] = c;
        nex[tot] = head[x];
        head[x] = tot ++ ;
        if(o)add(y, x, 0, -c, 0);
    }

    inline bool spfa(){//对费用 cost 求最短路
        //memset(dist, 0x3f, sizeof dist);//!0x3f3f3f3f3f -> 3f x 5
        for(int i = 1;i <= n; ++ i)dist[i] = INF;
        memset(vis, 0, sizeof vis);
        queue<int>q;
        q.push(S);
        dist[S] = 0;
        vis[S] = 1;
        while(q.size()){
            int x = q.front();
            q.pop();
            vis[x] = 0;
            for(int i = head[x]; ~i; i = nex[i]){
                int y = ver[i];
                ll z = edge[i], c = cost[i];
                if(dist[y] <= dist[x] + c || !z)continue;
                dist[y] = dist[x] + c;
                if(!vis[y])
                    q.push(y), vis[y] = 1;
            }
        }
        return dist[T] != INF;
    }


    ll dfs(int x, ll flow = INF){
        if(x == T)return flow;
        ll ans = 0, k, i;
        vis[x] = 1;
        for(i = cur[x]; ~i && flow; i = nex[i]){
            cur[x] = i;
            int y = ver[i];
            ll z = edge[i], c = cost[i];
            if(!z || (dist[y] != dist[x] + c) || vis[y])continue;
            k = dfs(y, min(flow, z));
            if(!k)dist[y] = INF;
            edge[i] -= k;
            edge[i ^ 1] += k;
            ans += k, mincost += k * c, flow -= k;
        }
        vis[x] = 0;
        return ans;
    }

    inline void main(){
        while(spfa()){
            /*for(int i = 1; i <= n; ++ i)
                cur[i] = head[i];*/
            memcpy(cur, head, sizeof head);
            ll now;
            while((now = dfs(S)))maxflow += now;//!
        }
    }

    inline void init(int _n, int _S, int _T){
        n = _n, S = _S, T = _T, tot = 0, maxflow = 0, mincost = 0;
        memset(head, -1, sizeof head);
    }
}

int n, m, S, T;
int a[1007][1007];
int main()
{
    scanf("%d%d", &m, &n);
    T = n + n * m + 1;
    for(int i = 1;i <= n; ++ i)
        for(int j = 1; j <= m; ++ j)
            scanf("%d", &a[i][j]);

    dinic::init(T, S, T);

    //把m个技术员拆成n * m 个点
    for(int i = 1; i <= n * m; ++ i)//每个技术员有m种选择
        dinic::add(S, i, 1, 0, 1);

    for(int i = 1; i <= m; ++ i)//m个技术员
    {
        for(int j = 1; j <= n; ++ j)
        {
            for(int k = 1; k <= n; ++ k)
            {
                int now = (i - 1) * n + k;
                dinic::add(now, j + n * m, 1, a[j][i] * k);
            }
        }
    }
    for(int i = 1; i <= n; ++ i)
        dinic::add(i + n * m, T, 1, 0);

    dinic::main();
    printf("%.2f\n", 1.0 * dinic::mincost / n);
    return 0;
}

