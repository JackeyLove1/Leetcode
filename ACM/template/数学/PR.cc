//
#include <cmath>

#define lll __int128
using ll = long long;
inline int f(int x,int c,int n)
{
    return (x*x+c)%n;
}

int pollard_rho(int N)
{
    int c=rand()%(N-1)+1;
    int t=f(0,c,N),r=f(f(0,c,N),c,N);//两倍速跑
    while(t!=r)
    {
        int d=std::gcd(abs(t-r),N);
        if(d>1)
            return d;
        t=f(t,c,N),r=f(f(r,c,N),c,N);
    }
    return N;//没有找到,重新调整参数c
}

inline ll PR(ll x)
{
    ll s=0,t=0,c=1ll*rand()%(x-1)+1;
    int stp=0,goal=1;
    ll val=1;
    for(goal=1;;goal<<=1,s=t,val=1)
    {
        for(stp=1;stp<=goal;++stp)
        {
            t=f(t,c,x);
            val=(lll)val*abs(t-s)%x;
            if((stp%127)==0)
            {
                ll d=gcd(val,x);
                if(d>1)
                    return d;
            }
        }
        ll d=gcd(val,x);
        if(d>1)
            return d;
    }
}


// Miller Rabin 快速测定素数
inline ll qp(ll x,ll p,ll mod)
{
    ll ans=1;
    while(p)
    {
        if(p&1)
            ans=(lll)ans*x%mod;
        x=(lll)x*x%mod;
        p>>=1;
    }
    return ans;
}
inline bool mr(ll x,ll b)
{
    ll k=x-1;
    while(k)
    {
        ll cur=qp(b,k,x);
        if(cur!=1 && cur!=x-1)
            return false;
        if((k&1)==1 || cur==x-1)
            return true;
        k>>=1;
    }
    return true;
}