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

// 线性筛求欧拉函数
const int N = 50007;
int n, m;
int vis[N];
int primes[N], phi[N], cnt;

void get_euler(int n) {
    phi[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) { // i是一个质数
            primes[++cnt] = i;
            phi[i] = i - 1; // 质数的性质,欧拉函数等于这个质数减一
        }
        for (int j = 1; j <= cnt && i * primes[j] <= n; ++j) {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0) {//最小的质因子
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            } else phi[i * primes[j]] = phi[i] * (primes[j] - 1);
        }
    }
}