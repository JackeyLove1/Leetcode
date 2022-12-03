#include<iostream>
#include<algorithm>
using namespace std;

const int N=10005;
const int INF=10000005;
struct node{int v,w,ne;}e[N<<1];
int h[N],idx; //加边
int del[N],siz[N],mxs,sum,root;//求根
int dis[N],d[N],cnt; //求距离
int ans[N],q[INF],judge[INF];//求路径
int n,m,ask[N];

void add(int u,int v,int w){
  e[++idx].v=v; e[idx].w=w;  
  e[idx].ne=h[u]; h[u]=idx;
}
void getroot(int u,int fa){
  siz[u]=1; 
  int s=0;
  for(int i=h[u];i;i=e[i].ne){
    int v=e[i].v;
    if(v==fa||del[v])continue;
    getroot(v,u);
    siz[u]+=siz[v];
    s=max(s,siz[v]);
  }
  s=max(s,sum-siz[u]);
  if(s<mxs) mxs=s, root=u;
}
void getdis(int u,int fa){
  dis[++cnt]=d[u];
  for(int i=h[u];i;i=e[i].ne){
    int v=e[i].v;
    if(v==fa||del[v])continue;
    d[v]=d[u]+e[i].w;
    getdis(v,u);
  }
}
void calc(int u){
  judge[0]=1;
  int p=0;
  // 计算经过根u的路径
  for(int i=h[u];i;i=e[i].ne){
    int v=e[i].v;
    if(del[v])continue;
    // 求出子树v的各点到u的距离
    cnt=0; 
    d[v]=e[i].w;
    getdis(v,u); 
    // 枚举距离和询问，判定答案
    for(int j=1;j<=cnt;++j)
      for(int k=1;k<=m;++k)
        if(ask[k]>=dis[j])
          ans[k]|=judge[ask[k]-dis[j]];
    // 记录合法距离      
    for(int j=1;j<=cnt;++j)
      if(dis[j]<INF)
        q[++p]=dis[j], judge[q[p]]=1;
  }
  // 清空距离数组
  for(int i=1;i<=p;++i) judge[q[i]]=0;  
}
void divide(int u){
  // 计算经过根u的路径
  calc(u); 
  // 对u的子树进行分治
  del[u]=1;
  for(int i=h[u];i;i=e[i].ne){
    int v=e[i].v;
    if(del[v])continue;
    mxs=sum=siz[v];
    getroot(v,0); //求根
    divide(root); //分治
  }
}
int main(){
  scanf("%d%d",&n,&m);
  for(int i=1;i<n;++i){
    int u,v,w;
    scanf("%d%d%d",&u,&v,&w);
    add(u,v,w);add(v,u,w);
  }
  for(int i=1;i<=m;++i)
    scanf("%d",&ask[i]);
  mxs=sum=n;
  getroot(1,0); 
  getroot(root,0); //重构siz[] 
  divide(root);
  for(int i=1;i<=m;++i)
    ans[i]?puts("AYE"):puts("NAY");
  return 0;
}