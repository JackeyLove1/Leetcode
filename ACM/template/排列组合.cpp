#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 2010, mod = 100003;

int fact[N], infact[N];

int qmi(int a, int k)
{
    int res = 1;
    while (k)
    {
        if (k & 1) res = (LL)res * a % mod;
        a = (LL)a * a % mod;
        k >>= 1;
    }
    return res;
}

// 求组合数
int C(int a, int b)
{
    if (a < b) return 0;
    return (LL)fact[a] * infact[a - b] % mod * infact[b] % mod;
}

// 求排列数
int P(int a, int b)
{
    if (a < b) return 0;
    return (LL)fact[a] * infact[a - b] % mod;
}

void init(){
    // 初始化求解
    fact[0] = infact[0] = 1;
    for (int i = 1; i < N; i ++ )
    {
        fact[i] = (LL)fact[i - 1] * i % mod;
        infact[i] = (LL)infact[i - 1] * qmi(i, mod - 2) % mod;
    }
}

int main()
{

    init();
    int a, b, c, d, k;
    cin >> a >> b >> c >> d >> k;

    int res = 0;
    for (int i = 0; i <= k; i ++ )
    {
        res = (res + (LL)C(b, i) * P(a, i) % mod * C(d, k - i) % mod * P(a + c - i, k - i)) % mod;
    }

    cout << res << endl;

    return 0;
}
