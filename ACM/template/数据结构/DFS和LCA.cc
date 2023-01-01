#include<bits/stdc++.h>
#define endl '\n'
#define int long long 
using namespace std;
const int mod=998244353;
int n,q;
vector<int> e[300001];
int d[300001],prt[300001],f[300001][31];
int sum[300001][51];
void dfs(int u,int fa)
{
	int tmp=1;
//	cout<<u<<endl;
	for(int i=1;i<=50;i++){
		tmp=(tmp*d[u])%mod;
		sum[u][i]=(sum[prt[u]][i]+tmp)%mod;
//		cout<<"\t"<<sum[u][i]<<endl;
	}
	for(auto v:e[u])if(v!=fa){
		d[v]=d[u]+1;
		prt[v]=u;
		dfs(v,u);
	}	
}
void ST()
{
	for(int i=1;i<=n;i++) f[i][0]=prt[i];
	for(int j=1;j<=30;j++){
		for(int i=1;i<=n;i++){
			f[i][j]=f[f[i][j-1]][j-1];
		}
	}
}
int Lca(int u,int v)
{
	if(d[u]<d[v]) swap(u,v);
	int k=30;
	for(int i=k;i>=0;i--){
		if(d[u]-(1<<i)>=d[v]){
			u=f[u][i];
		}
	}
	if(u==v) return u;
	for(int i=k;i>=0;i--){
		if(f[u][i]==f[v][i]) continue;
		u=f[u][i];
		v=f[v][i];
	}
	return f[u][0];
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
//	int rt;
	cin>>n;
//	cin>>rt;
	for(int i=1,x,y;i<n;i++){
		cin>>x>>y;
		e[x].push_back(y);
		e[y].push_back(x);
	}
	cin>>q;
	dfs(1,0);
	ST();
	while(q--)
	{
		int x,y,z;
		cin>>x>>y>>z;
		int l=Lca(x,y);
//		cout<<l<<endl;
		cout<<((sum[x][z]+sum[y][z])%mod-(sum[l][z]+sum[prt[l]][z])%mod+mod)%mod<<endl;
	}	
	return 0;
}