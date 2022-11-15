#include <bits/stdc++.h>

using namespace std;
constexpr int N = 1e5 + 100, M = 1e4 + 1;
int primes[N], mu[N], cnt{0};
bool vis[N];
inline void fhj(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

void get_mu(int n) {
    mu[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) {
            primes[cnt++] = i;
            mu[i] = -1;
        }
        for (int j = 0; i * primes[j] <= n; ++j) {
            int m = i * primes[j];
            vis[m] = true;
            if (i % primes[j]) {
                mu[m] = 0;
                break;
            } else {
                mu[m] = -mu[i];
            }
        }
    }
}
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
using ll = long long;
inline ll qpow(ll a, int b, int p){
    ll res = 1;
    while (b){
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

int main() {
    fhj();
    int a, m;
    cin >> a >> m;
    string b;
    cin >> b;
    auto ph = phi(m);
    int numb = 0;
    auto flag = false;
    for(const auto c : b){
        numb = (numb * 10 + c - '0');
        if (numb > ph){
            flag = true;
            numb %= ph;
        }
    }
    if (flag) numb += ph;
    cout << qpow(a, numb, m) << endl;
    return 0;
}
