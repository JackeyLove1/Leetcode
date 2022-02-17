/*
斯坦纳树问题是组合优化问题，与最小生成树相似，是最短网络的一种。
最小生成树是在给定的点集和边中寻求最短网络使所有点连通。
而最小斯坦纳树允许在给定点外增加额外的点，使生成的最短网络开销最小。
一个无向图，k个关键点，每个边有边权，求联通这k个点的最小代价
最小生成树可以认为是斯坦纳树的特殊情况
由于k个关键点的高度要求精确打击，只能用状压
f[i][S]以i为根的树，连接了S集合关键点，的最少代价
外层循环S

第一个dp：f[i][S]=min(f[i][t]+f[i][S^t])直接通过自己原来的构造转移

第二个dp：f[i][S]=min(f[i][S],f[k][S]+e[i][k])通过别的点连一条边过来

第二个dp明显有环，所以spfa处理一下

第一个dp更新完了之后，所有不是inf的点都加入queue，然后spfa/dijkstra


*/
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f3f3f3f
using namespace std;
const int maxn=510;
const int INF=0x3f3f3f3f;
typedef long long ll;
typedef pair<int,int> PII;
int n,m,k,u,v,w;
struct E{
	int to,next,dis;	
}edge[maxn<<1];

int head[maxn<<1],tree[maxn<<1],cnt;
int dp[maxn][5005],vis[maxn];
//dp[i][j]表示以i为根的一棵树，包含集合j中所有点的最小边权值和 
int key[maxn];  //关键点 
priority_queue<PII,vector<PII>,greater<PII> >q;

void addedge(int from,int to,int dis){
	edge[++cnt].next=head[from];
	edge[cnt].to=to;
	edge[cnt].dis=dis;
	head[from]=cnt;
	tree[cnt]=to; 
}

void dijkstra(int s){  //迪杰斯特拉堆优化算法 
	memset(vis,0,sizeof(vis));
	while(!q.empty()){
		PII fro=q.top();
		q.pop();	
		if(vis[fro.second]) continue;
		vis[fro.second]=1;
		for(int i=head[fro.second];i;i=edge[i].next){
			if(dp[tree[i]][s]>dp[fro.second][s]+edge[i].dis){
				dp[tree[i]][s]=dp[fro.second][s]+edge[i].dis;
				//再当前子集连通状态下进行边的松弛操作 
				q.push(PII(dp[tree[i]][s],tree[i]));
			}
		}
	}
} 

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	memset(dp,INF,sizeof(dp));
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){ //建无向图 
		cin>>u>>v>>w;
		addedge(u,v,w);
		addedge(v,u,w);
	}
	for(int i=1;i<=k;i++){
		cin>>key[i]; 
		dp[key[i]][1<<(i-1)]=0;
	}
	for(int s=1;s<(1<<k);s++){ //表示点集
		for(int i=1;i<=n;i++){  //中间部分
			for(int subs=s&(s-1);subs;subs=s&(subs-1)) //子图 
				dp[i][s]=min(dp[i][s],dp[i][subs]+dp[i][s^subs]);
			if(dp[i][s]!=INF) q.push(PII(dp[i][s],i));	
		}
		dijkstra(s);
	}
	cout<<dp[key[1]][(1<<k)-1]<<endl;
	return 0;
}


/*
#include<bits/stdc++.h>
#define il inline
#define reg register int
#define numb (ch^'0')
using namespace std;
typedef long long ll;
il void rd(int &x){
    char ch;bool fl=false;
    while(!isdigit(ch=getchar()))(ch=='-')&&(fl=true);
    for(x=numb;isdigit(ch=getchar());x=x*10+numb);
    (fl==true)&&(x=-x);
}
namespace Miracle{
const int N=11;
const int P=101;
const int inf=0x3f3f3f3f;
int mv[4][2]={{+1,0},{-1,0},{0,+1},{0,-1}};
int f[N][N][1<<10];
pair<int,int>pre[N][N][1<<10];
int id[N][N];
struct po{
    int x,y;
    po(){}
    po(int xx,int yy){
        x=xx;y=yy;
    }
};
queue<po>q;
int n,m,k;
int mp[N][N];
char op[N][N];
bool vis[N][N];
void spfa(int s){
    while(!q.empty()){
        po now=q.front();q.pop();
        vis[now.x][now.y]=0;
        for(reg i=0;i<4;++i){
            int dx=now.x+mv[i][0],dy=now.y+mv[i][1];
            if(dx<1||dx>n) continue;
            if(dy<1||dy>m) continue;
            if(f[dx][dy][s]>f[now.x][now.y][s]+mp[dx][dy]){
                f[dx][dy][s]=f[now.x][now.y][s]+mp[dx][dy];
                pre[dx][dy][s]=make_pair(now.x,now.y);
                if(!vis[dx][dy]){
                    vis[dx][dy]=1;
                    q.push(po(dx,dy));
                }
            }
        }
    }
}

void check(int i,int j,int s){
    if(id[i][j]==0) op[i][j]='o';
    if(pre[i][j][s].first!=-1){
        if(pre[i][j][s].first==0){
            check(i,j,pre[i][j][s].second);
            check(i,j,s^pre[i][j][s].second);
        }else{
            check(pre[i][j][s].first,pre[i][j][s].second,s);
        }
    }else return;
}
int main(){
    rd(n);rd(m);
    for(reg i=1;i<=n;++i){
        for(reg j=1;j<=m;++j){
            rd(mp[i][j]);
            if(mp[i][j]==0){
                ++k;id[i][j]=k;
                op[i][j]='x';
            }
            
        }
    }    
    memset(f,inf,sizeof f);
    for(reg i=1;i<=n;++i){
        for(reg j=1;j<=m;++j){
            if(mp[i][j]==0){
                f[i][j][1<<(id[i][j]-1)]=0;
                pre[i][j][1<<(id[i][j]-1)]=make_pair(-1,-1);
            }
            f[i][j][0]=0;
            pre[i][j][0]=make_pair(-1,-1);
        }
    }
    for(reg s=1;s<(1<<k);++s){
        for(reg i=1;i<=n;++i){
            for(reg j=1;j<=m;++j){
                for(reg t=(s-1)&s;t;t=(t-1)&s){
                    if(f[i][j][s]>f[i][j][t]+f[i][j][s^t]-mp[i][j]){
                        f[i][j][s]=f[i][j][t]+f[i][j][s^t]-mp[i][j];
                        pre[i][j][s]=make_pair(0,t);
                    }
                }
                if(f[i][j][s]!=inf) q.push(po(i,j)),vis[i][j]=1;
            }
        }
        spfa(s);
    }
    int tx,ty;
    int ans=inf;
    for(reg i=1;i<=n;++i){
        for(reg j=1;j<=m;++j){
            if(f[i][j][(1<<k)-1]<ans){
                ans=f[i][j][(1<<k)-1];
                tx=i;ty=j;            
            }
        }
    }
    check(tx,ty,(1<<k)-1);
    printf("%d\n",ans);
    for(reg i=1;i<=n;++i){
        for(reg j=1;j<=m;++j){
            if(!op[i][j]) op[i][j]='_';
            putchar(op[i][j]);
        }puts("");
    }
    return 0;
}

}
int main(){
    Miracle::main();
    return 0;
}
*/