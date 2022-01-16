#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<set>
#define MAXN 100005
#define LL long long
#define INF 2147483647
#define MOD 1000000007
#define free(s) freopen("s.txt","r",stdin);
#define lowbit(x) ((x&(-x))) 
#define debug(x) cout<<x<<endl;
using namespace std;
const int L=1005;
int n,f[60][262145],ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int t;
		scanf("%d",&t);
		f[t][i]=i+1;
	}
	for(int i=2;i<=58;i++)
		for(int j=1;j<=n;j++)
		{
			if(!f[i][j])
				f[i][j]=f[i-1][f[i-1][j]];
			if(f[i][j])
				ans=i;
		}
	printf("%d",ans);
	return 0;
}