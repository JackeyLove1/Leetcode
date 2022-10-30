#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

const int N=55,mod=1e9+7;

int f[N][N],ne[N];
char str[N];//子串

int main()
{
    int n,m;
    cin>>n>>str+1;
    m=strlen(str+1);

    for(int i=2,j=0;i<=m;i++)//求出ne数组(kmp模板)
    {
        while(j&&str[j+1]!=str[i]) j=ne[j];
        if(str[j+1]==str[i]) j++;
        ne[i]=j;
    }

    f[0][0]=1;//已经匹配了0位,且匹配的子串的位置是0时的方案数为1;(初始化)
    for(int i=0;i<n;i++)//枚举密码位
     for(int j=0;j<m;j++)//把第i位密码匹配到的子串位置都枚举一遍
     //j表示第i位密码匹配到的位置,因为不能包含子串,所以不能匹配到m这个位置
      for(char k='a';k<='z';k++)//把第i+1所有可能的字母都枚举一遍
       {
           //匹配过程:寻找当第i+1的位置是k时,并且密码已经生成了第i位,匹配的子串的位置是j时,能跳到哪个位置
           int u=j;
           while(u&&str[u+1]!=k) u=ne[u];
           if(str[u+1]==k) u++;

           if(u<m) f[i+1][u]=(f[i+1][u]+f[i][j])%mod;
           //因为是从f[i][j](i+1的位置为k)跳到f[i+1][u]这个位置,所以f[i+1][u]=f[i+1][u]+f[i][j];
           /*
           注:可能存在重边,因为j不同但ne[j]是相同的,并且k是相同的,所以此时
           f[i][j1]和f[i][j2]跳到的位置是一样的(k相同,ne[j1]=ne[j2])
           */
       }

    int res=0;
    for(int i=0;i<m;i++) res=(res+f[n][i])%mod;
    //将所有的方案数加起来即为总方案数
    printf("%d",res);

    return 0;
}