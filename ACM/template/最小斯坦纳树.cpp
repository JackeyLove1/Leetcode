#include <bits/stdc++.h>
using namespace std;
const int MAXN=510;
int n,m,k,x,y,z,eg,p[MAXN],hd[MAXN],ver[2*MAXN],vis[MAXN],nx[2*MAXN],edge[2*MAXN],dp[MAXN][4200];
priority_queue < pair<int,int> > q;
void add_edge (int x,int y,int z) {
	ver[++eg]=y;
	nx[eg]=hd[x],edge[eg]=z;
	hd[x]=eg;
	return;
}
void dijkstra (int s) {
	memset(vis,0,sizeof(vis));
	while (!q.empty()) {
		pair <int,int> a=q.top();
		q.pop();
		if (vis[a.second]) {continue;}
		vis[a.second]=1;
		for (int i=hd[a.second];i;i=nx[i]) {
			if (dp[ver[i]][s]>dp[a.second][s]+edge[i]) {
				dp[ver[i]][s]=dp[a.second][s]+edge[i];
				q.push(make_pair(-dp[ver[i]][s],ver[i]));
			}
		}
	}
	return;
}
int main () {
	freopen("st010.in","r",stdin);
	freopen("st010.out","w",stdout);
	memset(dp,0x3f,sizeof(dp));
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		add_edge(x,y,z),add_edge(y,x,z);
	}
	for (int i=1;i<=k;i++) {
		scanf("%d",&p[i]);
		dp[p[i]][1<<(i-1)]=0;
	}
	for (int s=1;s<(1<<k);s++) {
		for (int i=1;i<=n;i++) {
			for (int subs=s&(s-1);subs;subs=s&(subs-1)) {
				dp[i][s]=min(dp[i][s],dp[i][subs]+dp[i][s^subs]);
			}
			if (dp[i][s]!=0x3f3f3f3f) {q.push(make_pair(-dp[i][s],i));}
		}
		dijkstra(s);
	}
	printf("%d\n",dp[p[1]][(1<<k)-1]);
	return 0;
}
