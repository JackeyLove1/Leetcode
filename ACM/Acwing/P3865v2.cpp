#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
#include<math.h>

#define ls (p<<1)
#define rs (p<<1|1)
#define mid (l+r)/2
#define over(i,s,t) for(register long long i=s;i<=t;++i)
#define lver(i,t,s) for(register long long i=t;i>=s;--i)

using namespace std;
typedef long long ll;//全用ll可能会MLE或者直接WA,试着改成int看会不会A
const ll N=500007;
const ll INF=1e9+9;
const ll mod=2147483647;
const double EPS=1e-10;//-10次方约等于趋近为0
const double Pi=3.1415926535897;
ll n,m,f[N][21],a[N];

inline void ST()
{
    for(int i=1;i<=n;++i)
        f[i][0]=a[i];//初始化,以自己为起点2^0=1长的区间就是他自己
    for(int j=1;(1<<j)<=n;++j)//枚举区间长度
        for(ll i=1;i+(1<<j)-1<=n;++i)//枚举起点
            f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);//取最大值
} // 2^j 分割成为两个2 ^ (j-1)区间求解最大值

inline ll query(ll l,ll r)
{
    ll k=trunc(log2(r-l+1)); // 取半法获得最值
    return max(f[l][k],f[r-(1<<k)+1][k]);//因为已经用区间DP初始化过了，所以直接比较输出即可
}

int main()
{
    scanf("%lld%lld",&n,&m);
    over(i,1,n)scanf("%lld",&a[i]);
    ST();
    over(i,1,m)
    {
        ll x,y;
        scanf("%lld%lld",&x,&y);
        printf("%lld\n",query(x,y));
    }
    return 0;
}

