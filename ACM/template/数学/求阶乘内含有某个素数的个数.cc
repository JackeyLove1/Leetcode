const int maxn = 1e6+10;
using ll = long long;
int prime[maxn];//素数 
int cnt;
int fac[1234]; //素因子 
int num;
int expo[1234];//K的指数 
bool vis[maxn];
ll res;
void init()
{
    memset(vis,0,sizeof(vis));
    cnt = 0;
    for(int i = 2; i<maxn;i++)
    {
        if(!vis[i]){
            prime[cnt++] = i;
            for(int j = i+i;j<maxn;j+=i){
                vis[j] = 1;
            }
        }
    }
}
void getfactor(int x)
{
    num = 0;
    memset(expo,0,sizeof(expo));
    int n=sqrt(x);
    for(int i=0;i<cnt && prime[i]<=n;i++)
    {
        if(x%prime[i]==0)
        {
            fac[num] = prime[i];  
            while(x%prime[i]==0){
                expo[num]++;//K的指数 
                x/=prime[i];
            }
            num++;
        }
    }
    if(x>1){
        fac[num] = x;
        expo[num++] = 1;
    }
}
// get the number of p in n! 
ll solve(int n,int p)
{
    if(n<p)return 0;
    return solve( n / p , p) + 1LL* n / p;
}

/*
constexpr int N = 1e6 + 10, M = 1250;
int primes[N];
PII factors[M];
bool st[N];
int cntf, num, cnt, cntd;
ll res;

// 获得n范围内所有质数
inline void get_primers(int n) {
    memset(st, false, sizeof st);
    for (int i = 2; i <= n; ++i) {
        if (!st[i]) {
            primes[cnt++] = i;
            for (int j = 0; primes[j] <= n / i; ++j) {
                st[primes[j] * i] = true;
                if (i % primes[j] == 0) break;
            }
        }
    }
}

inline void get_factor(int d) {
    cntf = 0;
    // memset(factor, 0, sizeof factor);
    for (int i = 0; primes[i] <= d / primes[i]; ++i) {
        int p = primes[i];
        if (d % p == 0) {
            int s = 0;
            while (d % p == 0) ++s, d /= p;
            factors[++cntf] = {p, s};
        }
    }
    if (d > 1) factors[++cntf] = {d, 1};
}

ll solve(int n, int p) {
    return n < p ? 0 : (solve(n / p, p) + 1ll * (n / p));
}
*/