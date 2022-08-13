#include<bits/stdc++.h>
using namespace std;

inline int read()
{
    int x=0,y=1;char c=getchar();
    while (c<'0'||c>'9') {if (c=='-') y=-1;c=getchar();}
    while (c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
    return x*y;
}

const int N=205, M=10005<<1, INF=0x3f3f3f3f;

int n, m, S, T;
struct node{
    int to, c, rc, w, next; // c 表示容量（进行 capacity scaling ），rc 表示原图容量，w 表示费用。
}e[M];

int h[N], tot;

void add(int u, int v, int rc, int w){
    e[tot].to=v, e[tot].rc=rc, e[tot].w=w, e[tot].next=h[u], h[u]=tot++;
    e[tot].to=u, e[tot].rc=0, e[tot].w=-w, e[tot].next=h[v], h[v]=tot++;
}

int d[N], pre[N];
bool vis[N];
int q[N];

void spfa(int s){
    memset(vis, false, sizeof vis);
    memset(d, 0x3f, sizeof d);
    memset(pre, -1, sizeof pre);
    int tt=0, hh=0;
    d[s]=0, vis[s]=true, q[tt++]=s;

    while(tt!=hh){
        int hd=q[hh++]; if(hh==N) hh=0; 
        vis[hd]=false;

        for(int i=h[hd]; ~i; i=e[i].next){
            int go=e[i].to;
            if(e[i].c && d[go]>d[hd]+e[i].w){
                d[go]=d[hd]+e[i].w;
                pre[go]=i;
                if(!vis[go]){
                    vis[go]=true;
                    q[tt++]=go; if(tt==N) tt=0;
                }
            }
        }
    }
}

void add_one_cap(int id){
    // 优化，有流量的话，不可能关于这条边还存在负圈，直接更新后 return。
    if(e[id].c){
        e[id].c++;
        return;
    }
    int u=e[id^1].to, v=e[id].to; // from and to
    spfa(v);
    if(d[u]<INF && d[u]+e[id].w<0){
        e[id^1].c++;
        int x=u;
        while(x!=v){
            int t=pre[x];
            e[t].c--, e[t^1].c++;
            x=e[t^1].to;
        }
    }else e[id].c++;
}

int main(){
    memset(h, -1, sizeof h);
    n=read(), m=read(), S=read(), T=read();

    while(m--){
        int u, v, rc, w; u=read(), v=read(), rc=read(), w=read();
        add(u, v, rc, w);
    }

    add(T, S, INF, -INF);

    for(int i=32; i>=0; i--){ // 取决于 logU 的大小
        for(int j=0; j<tot; j++) e[j].c<<=1;
        for(int j=0; j<tot; j+=2) if(e[j].rc>>i&1) add_one_cap(j); // 传入边的编号 id，进行 +1 容量操作。
    }

    int cost=0;
    for(int i=0; i<tot-2; i+=2) cost+=e[i].w*e[i^1].c;
    cout<<e[tot-1].c<<' '<<cost<<endl;

    return 0;
}
