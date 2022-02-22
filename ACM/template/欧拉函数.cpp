// 在数论，对正整数n，欧拉函数是小于或等于n的正整数中与n互质的数的数目
// 在分解质因数的同时求解欧拉函数
inline int euler_one(int n) {
    int res = n;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            res = res / i * (i - 1);
            while (n % i == 0)n /= i;
        }
    }
    if (n > 1)res = res / n * (n - 1);
    return res;
}

const int N = 1e7 + 10;
using ll = long long ;
int primes[N], cnt;
bool st[N];
int phi[N];
ll s[N];


void init(int n)
{
    for (int i = 2; i <= n; i ++ )
    {
        if (!st[i])
        {
            primes[cnt ++ ] = i;
            phi[i] = i - 1;
        }
        for (int j = 0; primes[j] * i <= n && j < cnt; j ++ )
        {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0)//情况1 primes[j]是i的最小质因子
            {
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
            phi[i * primes[j]] = phi[i] * (primes[j] - 1);
        }
    }
    // 求phi函数的前缀和
    for (int i = 1; i <= n; i ++ ) s[i] = s[i - 1] + phi[i];
}