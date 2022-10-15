/*
SPFA算法是一种鉴于队列的实现算法.每一次有节点加入队列都是加入队尾.
但是SLF优化,不同于一般的SPFA算法,它是一种利用双端队列算法处理的问题.
如果说当前点所花费的值少于我们当前队头点的值的话,那么我们就将这个节点插入到队头去,
否则我们还是插入到队尾.
*/
#include <bits/stdc++.h>
using namespace std;
const int N=400000 +100;
int head[N],ver[N],Next[N],edge[N],vis[N],dis[N],tot;
void add_edge(int a,int b,int c)
{
    edge[tot]=b;
    ver[tot]=c;
    Next[tot]=head[a];
    head[a]=tot++;
}
void spfa(int s)
{
    memset(dis,0x3f,sizeof(dis));
    memset(vis,false,sizeof(vis));
    deque<int> q;
    dis[s]=0;
    vis[s]=true;
    q.push_back(s);
    while(q.size())
    {
        int now=q.front();
        vis[now]=false;
        q.pop_front();
        for(int i=head[now]; ~i; i=Next[i])
        {
            int j=edge[i];
            if (dis[j]>dis[now]+ver[i])
            {
                dis[j]=dis[now]+ver[i];
                if (!vis[j])
                {
                    vis[j]=true;
                    if (q.size() && dis[j]<dis[q.front()])
                        q.push_front(j); // 小于front插入front
                    else
                        q.push_back(j); // 否则back
                }
            }
        }
    }
}
int main()
{
    int t,r,p,s,x,y,z;
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>t>>r>>p>>s;
    memset(head,-1,sizeof(head));
    for(int i=1; i<=r; i++)
    {
        cin>>x>>y>>z;
        add_edge(x,y,z);
        add_edge(y,x,z);
    }
    for(int i=1; i<=p; i++)
    {
        cin>>x>>y>>z;
        add_edge(x,y,z);
    }
    spfa(s);
    for(int i=1; i<=t; i++)
    {
        if (dis[i]==0x3f3f3f3f)
            cout<<"NO PATH"<<endl;
        else
            cout<<dis[i]<<endl;
    }
    return 0;
}

/*
// SLF优化spfa
void spfa(int s) {
    memset(dist, 0x3f, sizeof dist);
    memset(st, false, sizeof st);
    deque<int> q;
    q.push_back(s), dist[s] = 0;
    while (!q.empty()) {
        auto t = q.front();
        st[t] = false;
        q.pop_front();
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                if (!st[j]) {
                    if (!q.empty() && dist[q.front()] > dist[j]) {
                        q.push_front(j);
                    } else {
                        q.push_back(j);
                    }
                    st[j] = true;
                }
            }
        }
    }
}
*/