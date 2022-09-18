#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>
#include <numeric>

using namespace std;

using ll = long long;
using PII = pair<int, int>;

const int N = 1e6 + 10, M = 1250;
int primes[N];
bool st[N];
int cnt;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

// 获得n范围内所有质数
inline void init(int n) {
    cnt = 0;
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

inline int isPrime(int x) {
    int i;
    for (i = 2; i * i <= x; i++)
        if (x % i == 0)return 0;
    return 1;
}

int m, d;
ll n, ans;

bool solve(ll x) {
    auto check = [](ll d) -> bool {
        for (int i = 0; i < cnt && d <= primes[i]; ++i) {
            if (d % primes[i] == 0) {
                if (d % (1ll * primes[i] * primes[i])) {
                    return false;
                }
                d /= primes[i];
            }
        }
        return true;
    };
    if (check(x)) {
        ans = std::min(ans, std::abs(x * x - n));
        return true;
    }
    return false;
}

int main() {
    fhj();
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        ans = std::numeric_limits<ll>::max();
        ll x = static_cast<ll>(std::sqrt(n) + 0.5);
        for (int i = 0;; ++i) {
            if (solve(x + i) || solve(x - i)) {
                break;
            }
        }
        cout << ans << endl;
    }
}
