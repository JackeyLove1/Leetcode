#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long a , b;
long long  dp[20][20],num[20];
long long  dfs(int pos,bool limit,bool lead,int dig,long long sum)
//sum是一定需要存的一个变量，因为她表示的是操作答案，需要不断随dfs更新
{//limit为1表示有限制，lead为0表示有前导0
	long long ans=0;
	if (pos==0) return sum;//边界条件
	if(!limit&&lead&&dp[pos][sum]!=-1) return dp[pos][sum];//记忆化
	int up=9;
	if(limit) up=num[pos];//达到限制就设上限为当前位的数（不想用三目运算符
	for(int j=0;j<=up;j++)
		ans+=dfs(pos-1, (j==up)&&limit , lead||j , dig , sum+((j||lead)&&(j==dig)) );
	if(!limit&&lead) dp[pos][sum]=ans;
	return ans;
}//数位dp的操作
long long  work(long long x,int d)
{
	memset(dp,-1,sizeof(dp));//初始化
	int len=0;
	while(x)
	{
		num[++len]=x%10;//最高位在第一位 
		x/=10;
	}
	return	dfs(len,1,0,d,0);
}
int main()
{
	cin>>a>>b;
	for(int i=0;i<=9;i++)//九个digit
	{
		 if(i!=9)cout<<work(b,i)-work(a-1,i)<<" ";
		 else cout<<work(b,i)-work(a-1,i);
         //我也不知道最后边输出了空格会不会炸（手动滑稽）
	}
	return 1;
}