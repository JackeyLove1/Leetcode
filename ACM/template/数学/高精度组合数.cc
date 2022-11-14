#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 150, P = 1000;
int C[1000][100][N];

int qpow(int a, int b){//快速幂
  int res = 1;
  while(b){
    if(b & 1) res = res*a%P;
    a = a*a%P;
    b >>= 1;
  }
  return res;
}
void add(int c[],int a[],int b[]){//高精度
  for(int i = 0; i < N; i++){
    c[i] += a[i]+b[i];
    c[i+1] += c[i]/10;
    c[i] %= 10;
  }
}
void getC(int n, int k){//组合数
  for(int i=0; i<n; i++)
    for(int j=0; j<=i && j<k; j++)
      if(j == 0) C[i][j][0] = 1;
      else add(C[i][j],C[i-1][j],C[i-1][j-1]);  
}
int main(){
  int k, x;
  cin >> k >> x;
  int n = qpow(x%P, x);
  getC(n, k);
  int i = N-1;
  while(C[n-1][k-1][i]==0) i--;
  while(i>=0) printf("%d", C[n-1][k-1][i--]);
  return 0;
}

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 10010;
int prim[N], vis[N], cnt;

void get_prim(int n){ //筛素数
  for(int i = 2; i <= n; i ++){
    if(!vis[i]) prim[cnt++] = i;
    for(int j=0; i*prim[j]<=n; j++){
      vis[i*prim[j]] = 1;
      if(i%prim[j] == 0) break;
    }
  }
}
int get(int n,int p){ //n!中p的个数
  int s = 0;
  while(n) s += n/p, n /= p;
  return s;
}
int getps(int n,int m,int p){//C中p的个数
  return get(n,p)-get(m,p)-get(n-m,p);
}
void mul(int C[],int p,int &len){//高精度
  int t = 0;
  for(int i=0; i<len; i++){
    t += C[i]*p;
    C[i] = t%10;
    t /= 10;
  }
  while(t){
    C[len++] = t%10;
    t /= 10;
  }
}
int main(){
  int n, m;
  cin >> n >> m; 
  get_prim(n);
  int C[N], len=1; C[0]=1;
  for(int i=0; i<cnt; i++){
    int p = prim[i];
    int s = getps(n,m,p);
    while(s--) mul(C,p,len); 
  }
  for(int i=len-1; i>=0; i--) 
    printf("%d", C[i]);
  return 0;
}

