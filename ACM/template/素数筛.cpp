// 线性筛
const int N = 10005;
int n, primes[N], cnt;
bool vis[N];

inline void get_prime() {
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) primes[++cnt] = i;
        for (int j = 1; j <= cnt && i * primes[j] <= n; ++j) {
            vis[i * primes[j]] = 1;
            if (i % primes[j] == 0) break;
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