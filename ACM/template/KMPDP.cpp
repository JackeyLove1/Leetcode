#include <iostream>
#include <cstring>

using namespace std;

const int N = 25;

int n , m , mod;
char str[N];
int ne[N] , a[N][N];
void mul(int c[][N] , int a[][N] , int b[][N])
{
    static int t[N][N];
    memset(t , 0 , sizeof t);//如果写了static，就不能通过static int t[N][N] = 0的方式初始化，因为只会调用一次 

    for(int i = 0 ; i < m ; i++)
        for(int j = 0 ; j < m ; j++)
            for(int k = 0 ; k < m ; k++)
                t[i][j] = (t[i][j] + a[i][k] * b[k][j]) % mod;

    memcpy(c , t , sizeof t);
}

int qmi(int k)
{
    int f[N][N] = {1};//为了简化代码f数组开二维，其实只用到了f[0]

    while(k)
    {
        if(k & 1) mul(f , f , a);
        k >>= 1;
        mul(a , a, a);
    }

    int res = 0;
    for(int i = 0 ; i < m ; i++) res = (res + f[0][i]) % mod;
    return res;
}

int main()
{
    cin >> n >> m >> mod;
    cin >> str + 1;

    //kmp
    for(int i = 2 , j = 0 ; i < m ; i++)
    {
        while(j && str[j + 1] != str[i]) j = ne[j];
        if(str[j + 1] == str[i]) j++;
        ne[i] = j;
    }

    for(int j = 0 ; j < m ; j++)//当前长度是j
        for(int c = '0' ; c <= '9' ; c++)//枚举后一位添加的数字
        {
            int k = j;
            while(k && str[k + 1] != c) k = ne[k]; // 找到匹配的下一位
            if(str[k + 1] == c) k++;
            if(k < m) a[j][k]++;//添加完后一位后，与不吉利串的匹配长度是k，方案数++
        }

    cout << qmi(n) << endl;
    return 0;
}

/*
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
 
int n,m,len;
double p[30];
char s[15];
char key[30];
int nx[15];
double f[1005][15];
 
void getnx()
{
     nx[1]=0;
     for(int i=2,j=0;i<=len;i++)
     {
         while(j&&s[i]!=s[j+1])j=nx[j];
         if(s[j+1]==s[i])j++;
         nx[i]=j;
     }
 }
 
 int main()
 {
     while(true)
     {
         memset(nx,0,sizeof(nx));
29         for(int i=1;i<=26;i++)p[i]=0.00;
30         for(int i=0;i<=1001;i++)
31         {
32             for(int j=0;j<=11;j++)
33             {
34                 f[i][j]=0.00;
35             }
36         }
37         scanf("%d%d",&n,&m);
38         if(!n)return 0;
39         for(int i=1;i<=n;i++)
40         {
41             char c[5];
42             scanf("%s",c+1);
43             key[i]=c[1];
44             scanf("%lf",&p[i]);
45         }
46         scanf("%s",s+1);
47         len=strlen(s+1);
48         getnx();
49         f[0][0]=1.00;
50         for(int i=1;i<=m;i++)
51         {
52             for(int j=0;j<len;j++)
53             {
54                 for(int k=1;k<=n;k++)
55                 {
56                     int ps=j;
57                     while(ps&&s[ps+1]!=key[k])ps=nx[ps];
58                     if(s[ps+1]==key[k])ps++;
59                     f[i][ps]+=f[i-1][j]*p[k];
60                 }
61             }
62         }
63         double ans=0.00;
64         for(int i=1;i<=m;i++)ans+=f[i][len];
65         printf("%.2lf%%\n",ans*100.00);
66     }
67 }
*/