using ll = long long;

const int N = 1e6 + 10, mod = 1e9 + 7;

int n;
bool st[N];
int primes[N], cnt;

void get_primes(int n) {
    for (int i = 2; i <= n; ++ i) {
        if (!st[i]) primes[cnt ++ ] = i;
        for (int j = 0; primes[j] * i <= n; ++ j) {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

// 计算素约数个数
int get_factors(){
    get_primes(n);
    ll res = 1;
    for (int i = 0; i < cnt; ++ i) {
        int p = primes[i];
        int s = 0;
        for (int j = n; j; j /= p) s += j / p;
        res = (ll)(s + 1) * res % mod;
    }
    return res;
}