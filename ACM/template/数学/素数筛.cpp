// 线性筛
#include <cstring>
#include <cstdlib>
const int N = 1e5 + 10;
int n, primes[N], cnt;
bool vis[N];

inline void get_prime(int sz) {
    for (int i = 2; i <= sz; i++) {
        if (!vis[i]) primes[cnt++] = i;
        for (int j = 0; j <= cnt && i * primes[j] <= sz; ++j) {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

// 筛选范围内最大的素因子

inline void get_primes(const int n){
    memset(primes,0,sizeof(primes));
    primes[1]=1;
    for(int i=2;i<n;i++)//筛选所有范围内的最大素数因子
    {
    	if(primes[i]==0){
            for(int j=i;j<n;j+=i){
    		primes[j]=i;
		    }   
        }
	}
}

inline void init() {
    memset(st, false, sizeof st);
    for (int i = 2; i <= n; ++i) {
        if (!st[i]) primes.push_back(i);
        for (int j = 0; j < primes.size() && primes[j] * i <= n; ++j) {
            st[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

// 求欧拉函数
int phi(int n){
    int res = n;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            res = res / i * (i - 1); // 先除再乘防止溢出
        while (n % i == 0) // 每个质因数只处理一次，可以把已经找到的质因数除干净
            n /= i;
    }
    if (n > 1)
        res = res / n * (n - 1); // 最后剩下的部分也是原来的n的质因数
    return res;
}

int phi[MAXN];
void init(int n){
    for (int i = 1; i <= n; i++)
        phi[i] = i; // 除1外没有数的欧拉函数是本身，所以如果phi[i] = i则说明未被筛到
    for (int i = 2; i <= n; i++)
        if (phi[i] == i) // 未被筛到
            for (int j = i; j <= n; j += i) // 所有含有该因子的数都进行一次操作
                phi[j] = phi[j] / i * (i - 1);
}

// 求约数个数
#include <iostream>
using namespace std;

const int N = 1000010;
int p[N], vis[N], cnt;
int a[N]; //a[i]记录i的最小质因子的次数
int d[N]; //d[i]记录i的约数个数

void get_d(int n){ //筛法求约数个数
  d[1] = 1;
  for(int i=2; i<=n; i++){
    if(!vis[i]){
      p[++cnt] = i;
      a[i] = 1;
      d[i] = 2;
    }
    for(int j=1; i*p[j]<=n; j++){
      int m = i*p[j];
      vis[m] = 1;
      if(i%p[j] == 0){
        a[m] = a[i]+1;
        d[m] = d[i]/a[m]*(a[m]+1);
        break;
      } 
      else{
        a[m] = 1;
        d[m] = d[i]*2;
      }
    }
  }
}
int main(){
  int n;
  cin >> n;
  get_d(n);
  for(int i=1; i<=n; i++)
    printf("%d\n", d[i]);
  return 0;
}