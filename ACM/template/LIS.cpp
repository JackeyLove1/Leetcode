// 使用树状数组求的最长上升子序列问题
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
#include<math.h>
#include<vector>
#define ls (p<<1)
#define rs (p<<1|1)
#define mid (l+r)/2
#define over(i,s,t) for(register long long i=s;i<=t;++i)
#define lver(i,t,s) for(register long long i=t;i>=s;--i)
//#define int __int128
using namespace std;
typedef long long ll;//全用ll可能会MLE或者直接WA,试着改成int看会不会A
const ll N=200007;
const ll INF=1e10+9;
const ll mod=2147483647;
const double EPS=1e-10;//-10次方约等于趋近为0
const double Pi=3.1415926535897;

ll n,m,a[N],tree[N];

inline void update(ll k,ll x)
{
    while(k<N)
    {
        tree[k]=max(tree[k],x);
        k+=k&(-k);
    }
}
inline ll query(ll k)
{
    ll res=0;
    while(k)
    {
        res=max(res,tree[k]);
        k-=k&(-k);
    }
    return res;
}
int main()
{
    scanf("%lld",&n);
    vector<ll>v;
    over(i,1,n)
    {
        scanf("%lld",&a[i]);
        a[i]+=n-i;
        v.push_back(a[i]);
    }
    sort(v.begin(),v.end());
    over(i,1,n)
        a[i]=lower_bound(v.begin(),v.end(),a[i])-v.begin()+1;
    over(i,1,n)//从前往后走，先query前面的更新后面最大值
        update(a[i],query(a[i])+1);

    printf("%lld\n",n-query(n+1));//树状数组不能从0开始，必须从1开始
}
