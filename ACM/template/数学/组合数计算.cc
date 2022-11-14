void init()
{
    for(int i = 1; i <= 1000; ++ i)
    {
        for(int j = 0; j <= i; ++ j)
            if (j == 0) c[i][j] = 0;
            else c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
    }
}

// Lucas
#include <iostream>
using namespace std;

typedef long long LL;
const int N = 100010;
LL f[N], g[N];

LL qpow(LL a, int b, int p){
  LL res = 1;
  while(b){
    if(b & 1) res=res*a%p;
    a = a*a%p;
    b >>= 1;
  }
  return res;
}
void init(int p){
  f[0] = g[0] = 1;
  for(int i=1; i<=p; i++){
    f[i] = f[i-1]*i%p;
    g[i] = g[i-1]*qpow(i,p-2,p)%p;
  }   
}
LL getC(int n, int m, int p){
    if (m > n) return 0;
  return f[n]*g[m]*g[n-m]%p;
}
int lucas(LL n, LL m, int p){
  if(m==0) return 1;
  return lucas(n/p,m/p,p)*getC(n%p,m%p,p)%p;
}
int main(){
  int q, n, m, p;
  cin >> q;
  while(q--){
    cin >> n >> m >> p;
    init(p);
    printf("%d\n",lucas(n+m,n,p));
  }
  return 0;
}
