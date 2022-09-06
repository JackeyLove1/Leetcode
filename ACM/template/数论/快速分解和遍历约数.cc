#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <numeric>

using namespace std;
using ull = __int128;
using ll = long long;
using PII = pair<int, int>;

static inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 45000, M = 50;
int primes[N], cnt;
bool st[N];

PII factor[M];
int cntf;

int divider[N], cntd;

int gcd(int a, int b){
    return std::gcd(a, b);
}
// 获得n范围内所有质数
inline void get_primers(int n){
    memset(st, false, sizeof st);
    for(int i = 2; i <= n; ++i){
        if (!st[i]){
            primes[cnt++] = i;
            for(int j = 0; primes[j] <= n / i; ++j){
                st[primes[j] * i] = true;
                if (i % primes[j] == 0) break;
            }
        }
    }
}

// 分解质因数
inline void get_factor(int d){
    cntf = 0;
    // memset(factor, 0, sizeof factor);
    for (int i = 0; primes[i] <= d / primes[i]; ++i){
        int p = primes[i];
        if (d % p == 0){
            int s = 0;
            while (d % p == 0) ++s, d /= p;
            factor[++cntf] = {p,s};
        }
    }
    if (d > 1) factor[++cntf] = {d, 1};
}

// 快速获得所有约数
void dfs(int u, int p){
    if (u > cntf){
        divider[cntd++] = p;
        return ;
    }
    for (int i = 0; i <= factor[u].second; ++i){
        dfs(u+1, p);
        p *= factor[u].first;
    }
}

// 遍历所有b1的约数
inline void solve(int a0, int a1, int b0, int b1){
    get_factor(b1); // 分解质因数
    cntd = 0;
    dfs(1, 1); // 获取所有约数
    int res = 0;
    for (int i = 0; i < cntd; ++i){
        int x = divider[i];
        if (gcd(x, a0) == a1 && (ll)x * b0 / gcd(x, b0) == b1){
            ++res;
        }
    }
    cout << res << endl;
}

int main(){
    int m;
    cin >> m;
    get_primers(N-1);
    while (m--){
        int a0, a1, b0, b1;
        cin >> a0 >> a1 >> b0 >> b1;
        solve(a0, a1, b0, b1);
    }
    return 0;
}