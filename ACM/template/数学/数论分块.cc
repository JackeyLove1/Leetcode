#include<cstdio>
#include<algorithm>
using namespace std;

typedef long long LL;

int main(){
  LL n, k;
  scanf("%lld%lld", &n, &k);
  LL l = 1, r, res = n*k;
  while(l <= n){
    if(k/l) r = min(k/(k/l),n); 
    else r = n;
    res -= (k/l)*(r-l+1)*(l+r)/2;
    l = r+1;
  }
  printf("%lld", res);
  return 0;
}