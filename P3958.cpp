#include<bits/stdc++.h>
using namespace std;
const int mx=110;
int dp[mx*5][mx],n,w[mx],v[mx],sumv,minv=1e10,sv;
int main()
{
	cin>>n>>sumv;
	for (int i=1;i<=n;i++) cin>>v[i]>>w[i],minv=min(minv,v[i]),sv+=v[i];
	minv--;
        for (int i=1;i<=n;i++) v[i]-=minv;
        sv-=n*minv;
	for (int i=1;i<=n;i++)
	for (int j=sv;j>=v[i];j--)
	for (int k=n;k>=1;k--)
	if (j+k*minv<=sumv) dp[j][k]=max(dp[j][k],dp[j-v[i]][k-1]+w[i]);//cout<<dp[j][k]<<" "<<j<<" "<<k<<endl;
    
	int ans=0;
	for (int j=1;j<=sv;j++)
	for (int i=1;i<=n;i++) ans=max(ans,dp[j][i]);
	cout<<ans;
	return 0;
}
