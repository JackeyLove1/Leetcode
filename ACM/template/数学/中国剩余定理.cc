/*
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}
inline ll inv(ll a, ll p)
{
    ll x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}
// a是模数数组，b是余数数组，n是数组长度
inline ll CRT(ll a[], ll b[], ll n)
{
    ll p = 1, x = 0;
    for (int i = 0; i < n; ++i)
        p *= a[i];
    for (int i = 0; i < n; ++i)
    {
        ll r = p / a[i];
        x += (b[i] * r * inv(r, a[i])) % p;
    }
    return x % p;
}
int main()
{
    ll n, a[10], b[10];
    scanf("%lld", &n);
    for (int i = 0; i < n; ++i)
        scanf("%lld%lld", a + i, b + i);
    printf("%lld\n", CRT(a, b, n));
    return 0;
}
*/
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;


LL exgcd(LL a, LL b, LL &x, LL &y)
{
    if (!b)
    {
        x = 1, y = 0;
        return a;
    }

    LL d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}


int main()
{
    int n;
    cin >> n;

    LL x = 0, m1, a1;
    cin >> m1 >> a1;
    for (int i = 0; i < n - 1; i ++ )
    {
        LL m2, a2;
        cin >> m2 >> a2;
        LL k1, k2;
        LL d = exgcd(m1, m2, k1, k2);
        if ((a2 - a1) % d)
        {
            x = -1;
            break;
        }

        k1 *= (a2 - a1) / d;
        k1 = (k1 % (m2/d) + m2/d) % (m2/d);

        x = k1 * m1 + a1;

        LL m = abs(m1 / d * m2);
        a1 = k1 * m1 + a1;
        m1 = m;
    }

    if (x != -1) x = (a1 % m1 + m1) % m1;

    cout << x << endl;

    return 0;
}

// CRT
// C++ Version
LL CRT(int k, LL* a, LL* r) {
  LL n = 1, ans = 0;
  for (int i = 1; i <= k; i++) n = n * r[i];
  for (int i = 1; i <= k; i++) {
    LL m = n / r[i], b, y;
    exgcd(m, r[i], b, y);  // b * m mod r[i] = 1
    ans = (ans + a[i] * m * b % n) % n;
  }
  return (ans % n + n) % n;
}

// 模数互质
// 经典解法
typedef __int128 LL;
LL a[105],r[105];
int n;
LL exgcd(LL a,LL b,LL &x,LL &y)
{
    if(b==0){
        x=1;y=0;
        return a;
    }
    LL d=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
LL CRT()
{
    LL a1,r1,a2,r2,x,y;
    a1=a[1],r1=r[1];
    for(int i=2;i<=n;i++){
        a2=a[i];r2=r[i];
        LL c=r2-r1;
        LL d=exgcd(a1,a2,x,y);
        if(c%d) return -1;
        LL x0=c/d*x;
        LL t=a2/d;
        x0=(x0%t+t)%t;
        r1=r1+a1*x0;
        a1=a1/d*a2;
    }
    return r1;
}
int main()
{
    long long m;
    scanf("%d%lld",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%lld%lld",&a[i],&r[i]);
    LL ans=CRT();
    if(ans<0) printf("he was definitely lying\n");
    else if(ans>m) printf("he was probably lying\n");
    else printf("%lld\n",ans);
    return 0;
}

