#include<cstdio>  
#include<cmath>  
using namespace std;  
typedef long long ll;
#define maxn 5000005
bool is_prime[maxn];  
int prime[maxn],pi[maxn];  
int getprime()  
{  
    int cnt=0;  
    is_prime[0]=is_prime[1]=1;  
    pi[0]=pi[1]=0;  
    for(int i=2;i<maxn;i++)  
    {  
        if(!is_prime[i])prime[++cnt]=i;  
        pi[i]=cnt;  
        for(int j=1;j<=cnt&&i*prime[j]<maxn;j++)  
        {  
            is_prime[i*prime[j]]=1;  
            if(i%prime[j]==0)break;  
        }  
    }  
    return cnt;  
}  
const int M=7;  
const int PM=2*3*5*7*11*13*17;  
int phi[PM+1][M+1],sz[M+1];  
void init()  
{  
    getprime();  
    sz[0]=1;  
    for(int i=0;i<=PM;i++)phi[i][0]=i;  
    for(int i=1;i<=M;i++)  
    {  
        sz[i]=prime[i]*sz[i - 1];  
        for(int j=1;j<=PM;j++)phi[j][i]=phi[j][i-1]-phi[j/prime[i]][i-1];  
    }  
}  
int sqrt2(ll x)  
{  
    ll r=(ll)sqrt(x-0.1);  
    while(r*r<=x)r++;  
    return int(r-1);  
}  
int sqrt3(ll x)  
{  
    ll r=(ll)cbrt(x-0.1);  
    while(r*r*r<= x)r++;  
    return int(r-1);  
}  
ll getphi(ll x,int s)  
{  
    if(s==0)return x;  
    if(s<=M)return phi[x%sz[s]][s]+(x/sz[s])*phi[sz[s]][s];  
    if(x<=prime[s]*prime[s])return pi[x]-s+1;  
    if(x<=prime[s]*prime[s]*prime[s]&&x<maxn)  
    {  
        int s2x=pi[sqrt2(x)];  
        ll ans=pi[x]-(s2x+s-2)*(s2x-s+1)/2;  
        for(int i=s+1;i<=s2x;i++)ans+=pi[x/prime[i]];  
        return ans;  
    }  
    return getphi(x,s-1)-getphi(x/prime[s],s-1);  
}  
ll getpi(ll x)  
{  
    if(x<maxn)return pi[x];  
    ll ans=getphi(x,pi[sqrt3(x)])+pi[sqrt3(x)]-1;  
    for(int i=pi[sqrt3(x)]+1,ed=pi[sqrt2(x)];i<=ed;i++) 
        ans-=getpi(x/prime[i])-i+1;  
    return ans;  
}  
ll Lehmer_pi(ll x)  
{  
    if(x<maxn)return pi[x];  
    int a=(int)Lehmer_pi(sqrt2(sqrt2(x)));  
    int b=(int)Lehmer_pi(sqrt2(x));  
    int c=(int)Lehmer_pi(sqrt3(x));  
    ll sum=getphi(x,a)+(ll)(b+a-2)*(b-a+1)/2;  
    for(int i=a+1;i<=b;i++)  
    {  
        ll w=x/prime[i];  
        sum-=Lehmer_pi(w);  
        if(i>c)continue;  
        ll lim=Lehmer_pi(sqrt2(w));  
        for(int j=i;j<=lim;j++)sum-=Lehmer_pi(w/prime[j])-(j-1);  
    }  
    return sum;  
}  
int main()   
{  
    init();  
    ll n;  
    while(~scanf("%lld",&n))  
        printf("%lld\n",Lehmer_pi(n));  
    return 0;  
} 