/*
#include <bits/stdc++.h>

using namespace std;
constexpr int N = 1e5 + 100;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ll = long long;

inline ll qpow(ll a, ll b, ll p) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

inline ll BSGS(ll a, ll b, ll p) {
    unordered_map<ll, int> h;
    a %= p, b %= p;
    if (b == 1) return 0;
    ll m = static_cast<ll>(std::sqrt(p)) + 1;
    ll t = b;
    h[b] = 0;
    for (int j = 1; j <= m; ++j) {
        t = t * a % p;
        h[t] = j;
    }
    auto mi = qpow(a, m, p);
    t = 1;
    for (int i = 1; i <= m; ++i) {
        t = t * mi % p;
        if (h.count(t)) {
            return i * m - h[t];
        }
    }
    return -1;
}

int main() {
    int a, p, b;
    cin >> p >> a >> b;
    int res = BSGS(a, b, p);
    if (res == -1) puts("no solution");
    else cout << res << endl;
    return 0;
}
*/

/*
// exbsgs
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <unordered_map>
using namespace std;

typedef long long LL;

LL gcd(LL a, LL b){
  return b==0?a:gcd(b,a%b);
}
LL exbsgs(LL a, LL b, LL p){
  a %= p; b %= p;
  if(b==1||p==1)return 0;//x=0
  
  LL d, k=0, A=1;
  while(true){
    d = gcd(a,p);
    if(d==1) break;
    if(b%d) return -1; //无解
    k++; b/=d; p/=d;
    A = A*(a/d)%p; //求a^k/D
    if(A==b) return k;
  }
  
  LL m=ceil(sqrt(p));
  LL t = b;
  unordered_map<int,int> hash;
  hash[b] = 0;
  for(int j = 1; j < m; j++){
    t = t*a%p; //求b*a^j
    hash[t] = j;
  }
  LL mi = 1;
  for(int i = 1; i <= m; i++)
    mi = mi*a%p; //求a^m
  t = A;
  for(int i=1; i <= m; i++){
    t = t*mi%p; //求(a^m)^i
    if(hash.count(t)) 
      return i*m-hash[t]+k;
  }
  return -1; //无解
}
int main(){
  LL a, p, b;
  while((scanf("%lld%lld%lld",&a,&p,&b)!=EOF)&&a){
    LL res = exbsgs(a, b, p);
    if(res == -1) puts("No Solution");
    else printf("%lld\n",res);
  }
  return 0;
}

*/
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

typedef long long LL;
const int INF = 1e8;

int exgcd(int a, int b, int& x, int& y)
{
    if (!b)
    {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int bsgs(int a, int b, int p)
{
    if (1 % p == b % p) return 0;
    int k = sqrt(p) + 1;
    unordered_map<int, int> hash;
    for (int i = 0, j = b % p; i < k; i ++ )
    {
        hash[j] = i;
        j = (LL)j * a % p;
    }
    int ak = 1;
    for (int i = 0; i < k; i ++ ) ak = (LL)ak * a % p;
    for (int i = 1, j = ak; i <= k; i ++ )
    {
        if (hash.count(j)) return i * k - hash[j];
        j = (LL)j * ak % p;
    }
    return -INF;
}

int exbsgs(int a, int b, int p)
{
    b = (b % p + p) % p;
    if (1 % p == b % p) return 0;
    int x, y;
    int d = exgcd(a, p, x, y);
    if (d > 1)
    {
        if (b % d) return -INF;
        exgcd(a / d, p / d, x, y);
        return exbsgs(a, (LL)b / d * x % (p / d), p / d) + 1;
    }
    return bsgs(a, b, p);
}

int main()
{
    int a, p, b;
    while (cin >> a >> p >> b, a || p || b)
    {
        int res = exbsgs(a, b, p);
        if (res < 0) puts("No Solution");
        else cout << res << endl;
    }
    return 0;
}

/*
ll BSGS(ll a, ll b, ll m)
{
    static unordered_map<ll, ll> hs;
    hs.clear();
    ll cur = 1, t = sqrt(m) + 1;
    for (int B = 1; B <= t; ++B)
    {
        (cur *= a) %= m;
        hs[b * cur % m] = B; // 哈希表中存B的值
    }
    ll now = cur; // 此时cur = a^t
    for (int A = 1; A <= t; ++A)
    {
        auto it = hs.find(now);
        if (it != hs.end())
            return A * t - it->second;
        (now *= cur) %= m;
    }
    return -1; // 没有找到，无解
}

ll exBSGS(ll a, ll b, ll m, ll k = 1)
{
    ll A = a %= m, B = b %= m, M = m;
    if (b == 1) return 0;
    ll cur = 1 % m;
    for (int i = 0;; i++)
    {
        if (cur == B) return i;
        cur = cur * A % M;
        ll d = gcd(a, m);
        if (b % d) return -INF;
        if (d == 1) return BSGS(a, b, m, k * a % m) + i + 1;
        k = k * a / d % m, b /= d, m /= d; // 相当于在递归求解exBSGS(a, b / d, m / d, k * a / d % m)
    }
}

*/