namespace CRT {
int m;
constexpr int N = 1e5 + 100;
using ll = long long;
ll exgcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll d, x1, y1;
    d = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - a / b * y1;
    return d;
}

ll CRT(int m[], int r[], int n) {
    ll M = 1, ans = 0;
    for (int i = 1; i <= n; ++i) M *= m[i];
    for (int i = 1; i <= n; ++i) {
        auto c = M / m[i];
        ll x, y;
        exgcd(c, m[i], x, y);
        ans = (ans + c * x * r[i] % M) % M;
    }
    return (ans % M + M) % M;
}
}  // namespace CRT

namespace kmp {
constexpr int N = 1e5 + 10;
char s[N], t[N];
int ne[N];
inline void get_next(const char s[], int n){
    // s from 1 to n
    memset(ne, 0, sizeof ne);
    for(int i = 1, j = 0; i <= n; ++i){
        while (j && s[i] != s[j+1]) j = ne[j];
        if (s[i] == s[j+1]) ++j;
        ne[i] = j;  
    }
}

inline void kmp(const char s[], int n, const char t[], int m){
    get_next(s, n);
    for (int i = 1, j = 0; i <= m; ++i){
        while (j && s[j+1] != p[i]) j = ne[j];
        if (s[j+1] == p[i]) ++j;
        if (j == n){
            std::cout << i - n + 1 << std::endl;
            j = ne[j];
        }
    }
}
}


namespace prime {
constexpr int N = 1e5 + 100;
int primes[N], cnt;
bool vis[N];
inline void init(int n){
    memset(vis, false, sizeof vis);
    for (int i = 2; i <= n; ++i){
        if (!vis[i]) primes[cnt++] = i;
        for(int j = 0; primes[j] * i <= n; ++j){
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0){
                break;
            }
        }
    }
}
}