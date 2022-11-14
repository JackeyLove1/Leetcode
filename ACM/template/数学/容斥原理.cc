// #pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e5 + 100, M = 1e5 + 20, INF = 0x3f3f3f3f;
int c[5], d[5], n, m;
using ll = long long;
ll f[N];

inline void pre() {
    memset(f, 0, sizeof f);
    f[0] = 1;
    for (int i = 0; i < 4; ++i) {
        for (int j = c[i]; j <= M; ++j) {
            f[j] += f[j - c[i]];
        }
    }
}

using LL = long long;
inline int count(int s){
    int res = 0;
    while (s){
        res += s & 1;
        s >>= 1;
    }
    return res;
}
LL calc(LL s) { //容斥原理
    LL res = 0;
    for (int i = 1; i < 1 << 4; i++) {//枚举状态
        LL t = 0, sign = -1;
        for (int j = 0; j < 4; j++) //过滤状态
            if (i & 1 << j) {
                t += c[j] * (d[j] + 1);
                sign = -sign;
            }
        if (s >= t) res += f[s - t] * sign;
    }
    return f[s] - res;
}

int main() {
    fhj();
    for (int i = 0; i < 4; ++i) cin >> c[i];
    cin >> m;
    pre();
    while (m--) {
        for (int i = 0; i < 4; ++i) {
            cin >> d[i];
        }
        ll s;
        cin >> s;
        cout << calc(s) << endl;
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
const long long S = 1e5 + 5;
long long c[5], d[5], n, s;
long long f[S];

int main() {
  scanf("%lld%lld%lld%lld%lld", &c[1], &c[2], &c[3], &c[4], &n);
  f[0] = 1;
  for (long long j = 1; j <= 4; j++)
    for (long long i = 1; i < S; i++)
      if (i >= c[j]) f[i] += f[i - c[j]];  // f[i]：价格为i时的硬币组成方法数
  for (long long k = 1; k <= n; k++) {
    scanf("%lld%lld%lld%lld%lld", &d[1], &d[2], &d[3], &d[4], &s);
    long long ans = 0;
    for (long long i = 1; i < 16;
         i++) {  // 容斥，因为物品一共有4种，所以从1到2^4-1=15循环
      long long m = s, bit = 0;
      for (long long j = 1; j <= 4; j++) {
        if ((i >> (j - 1)) % 2 == 1) {
          m -= (d[j] + 1) * c[j];
          bit++;
        }
      }
      if (m >= 0) ans += (bit % 2 * 2 - 1) * f[m];
    }
    printf("%lld\n", f[s] - ans);
  }
  return 0;
}

