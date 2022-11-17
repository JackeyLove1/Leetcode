#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
    
int exgcd(int a,int b,int &x,int &y){
  if(b == 0){x = 1, y = 0; return a;}
  int x1, y1, d;
  d = exgcd(b, a%b, x1, y1);
  x = y1, y = x1-a/b*y1;
  return d;
}
int main(){
  int a, b, m, x, y;
  scanf("%d%d%d", &a, &b, &m);
  int d = exgcd(a, m, x, y);
  if(b%d == 0) 
    printf("%d", 1ll*x*b/d%m);
  else puts("none");
  return 0;
}

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
    
int exgcd(int a,int b,int &x,int &y){
  if(b == 0){
    x = 1, y = 0; return a;
  }
  int x1, y1, d;
  d = exgcd(b, a%b, x1, y1);
  x = y1, y = x1-a/b*y1;
  return d;
}
int main(){
  int a, m, x, y;
  scanf("%d%d", &a, &m);
  exgcd(a, m, x, y);
  printf("%d", (x%m+m)%m);
  return 0;
}