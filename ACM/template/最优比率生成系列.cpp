// 最优比率生成环
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
#include<map>

using namespace std;

const int N = 1e4+7;
const int M = 5e4+7;
const double eps = 1e-6;
int f[N];
int head[N],ver[M],nex[M],tot;
double edge[M];
int n,m;
int a[N];
double dis[N];
bool vis[N];//判断是否在队列里
int cnt[N];//表示的是从起点到x的最短路径包含的边数


void add(int x,int y,double z){
    ver[++tot] = y;
    nex[tot] = head[x];
    edge[tot] = z;
    head[x] = tot;
}
//判断是否存在负环，cnt[i]大于n则有负环（一共n个点，如果没有负环就最多等于n）
bool spfa(){
    queue<int>q;
    //没有起点，每个人都是起点
    for(int i = 1;i <= n;++i){
        q.push(i);
        dis[i] = 0;
        vis[i] = 1;
    }
    memset(cnt,0,sizeof cnt);
    while(q.size()){
        int x = q.front();
        q.pop();
        vis[x] = 0;
        for(int i = head[x];i;i = nex[i]){
            int y = ver[i];
            if(dis[y] > dis[x] + edge[i]){
                dis[y] = dis[x] + edge[i];
                if((cnt[y] = cnt[x] + 1 ) > n)return 1;
                if(!vis[y]){
                    q.push(y);
                    vis[y] = 1;
                }
            }
        }
        
    }
    return 0;
}
int x[N],y[N], z[N];

bool check(double w){
    tot = 0;
    memset(head,0,sizeof head);
    for(int i = 1;i <= m;++i)
        add(x[i],y[i],w * z[i] - f[x[i]]);//减去出点权值
    return spfa();
}

int main(){
    cin>>n>>m;
    for(int i = 1;i <= n;++i)
        scanf("%d",&f[i]);
    for(int i = 1;i <= m;++i)
        scanf("%d %d %d",&x[i],&y[i],&z[i]);
    double l = 0,r = 1000;
    while(r - l > eps){
        double mid = (l + r) / 2;
        if(check(mid))l = mid;
        else r = mid;
    }
    printf("%.2f",l);
    return 0;
}
