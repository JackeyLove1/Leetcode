#include<bits/stdc++.h>
using namespace std;
#define ll int
#define gc(a) a=getchar()
#define pc(a) putchar(a)
ll read(){
    char c;ll x=0;bool flag=0;gc(c);
    while(c<'0'||c>'9'){if(c=='-') flag=1;gc(c);}
    while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),gc(c);}
    return flag?-x:x;
}
void pr(ll x){
    if(x<0){x=-x;pc('-');}
    if(x>9) pr(x/10);
    pc(x%10+48);
}
//-------快读------
#define inf 0x3f3f3f3f
const ll maxn=10005;
const ll maxm=10005;
struct node
{
	ll id,h,l;
	bool operator <(const node &a) const
	{
		return id<a.id;
	}
}o[maxn];
ll x[maxn],y[maxn],dp[2][maxm],n,m,k,cnt=1,ans;
int main()
{
	//memset(dp,inf,sizeof(dp));//两个被遗忘的初始化之一qwq
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++)
	x[i]=read(),y[i]=read();
	for(int i=1;i<=k;i++)
	o[i].id=read(),o[i].l=read(),o[i].h=read();
	sort(o+1,o+k+1);//管道id排序!
	//for(int i=1;i<=m;i++)
	//dp[0][i]=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=m;j++)//注意要初始化！
		dp[i%2][j]=inf;
		for(int j=x[i]+1;j<=x[i]+m;j++)//p=1，完全背包
		dp[i%2][j]=min(dp[i%2^1][j-x[i]]+1,dp[i%2][j-x[i]]+1);
		for(int j=m+1;j<=x[i]+m;j++)//比m大的都是m
		dp[i%2][m]=min(dp[i%2][m],dp[i%2][j]);
		for(int j=1;j<=m-y[i];j++)//p=0，01背包
		dp[i%2][j]=min(dp[i%2][j],dp[i%2^1][j+y[i]]);
		if(i==o[cnt].id)//如果这个地方有管道
		{
			ans=inf;//主要每次都要初始化一次！
			for(int j=0;j<=o[cnt].l;j++)
			dp[i%2][j]=inf;
			for(int j=o[cnt].h;j<=m;j++)
			dp[i%2][j]=inf;
			for(int j=1;j<=m;j++)//寻找是否可以通过
			ans=min(dp[i%2][j],ans);
			if(ans==inf)
			{
				pr(0);pc('\n');pr(cnt-1);return 0;
			}
			cnt++;
		}
	}
	ans=inf;//注意要初始化！
	for(int j=1;j<=m;j++)
	ans=min(dp[n%2][j],ans);
	pr(1);pc('\n');pr(ans);
	return 0;
}