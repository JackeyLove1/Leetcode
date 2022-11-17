#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef __int128 LL;
const int N = 100005;
LL n, m[N], r[N];

LL exgcd(LL a,LL b,LL &x,LL &y){
  if(b==0){x=1, y=0; return a;}
  LL d, x1, y1;
  d = exgcd(b, a%b, x1, y1);
  x = y1, y = x1-a/b*y1;
  return d;
}
LL EXCRT(LL m[], LL r[]){
  LL m1, m2, r1, r2, p, q;
  m1 = m[1], r1 = r[1];
  for(int i=2; i<=n; i++){
    m2 = m[i], r2 = r[i];
    LL d = exgcd(m1,m2,p,q);
    if((r2-r1)%d){return -1;}
    p=p*(r2-r1)/d; //特解
    p=(p%(m2/d)+m2/d)%(m2/d);
    r1 = m1*p+r1;
    m1 = m1*m2/d;
  }
  return (r1%m1+m1)%m1;
}
int main(){
  scanf("%lld", &n);
  for(int i = 1; i <= n; ++i)
    scanf("%lld%lld", m+i, r+i);
  printf("%lld\n",EXCRT(m,r));
  return 0;
}