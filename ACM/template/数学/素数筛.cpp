// 线性筛
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


// 埃式筛
#include <cstring>

int v[N];
void get_primes(int n){
    memset(v, 0, sizeof(v));
    for(int i = 2; i <= n; i++){
        if (v[i]) continue;
        cout << i << endl;
        for(int j = 2; j <= n / i; ++j){
            v[i * j] = 1;
        }
    }
}