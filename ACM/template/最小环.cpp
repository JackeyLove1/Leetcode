#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int n,m,a[101][101],f[101][101],x,y,ans;
int main()
{
	memset(a,127/3,sizeof(a));//初始化
	memset(f,127/3,sizeof(f));//初始化
	ans=a[0][0];//初始化
	scanf("%d%d",&n,&m);//读入
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);//读入
		scanf("%d",&a[x][y]);//读入
		a[y][x]=f[x][y]=f[y][x]=a[x][y];//建邻接矩阵
	}
	for (int k=1;k<=n;k++)
	{
		for (int i=1;i<=k-1;i++)
		for (int j=i+1;j<=k-1;j++)
		ans=min(ans,f[i][j]+a[i][k]+a[k][j]);//求最小环
		for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		f[i][j]=min(f[i][j],f[i][k]+f[k][j]);//floyed算法求最短路
	}
	if (ans!=a[0][0]) printf("%d",ans);//如可到达则正常输出
	else printf("No solution");//否则输出NO solution
	return 0;
}
