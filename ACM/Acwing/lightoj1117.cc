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
#include <cmath>

using namespace std;
using sll = __int128;
using ull = unsigned long long;
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

constexpr int N = 1e3 + 100, INF = 0x3f3f3f3f, M = 26;

inline int popcount(int x) {
    return __builtin_popcount(x);
}

ll LCM(ll a, ll b){
    return a / __gcd(a, b) * b;
}

ll n, a[N];
int m;

int main() {
    fhj();
    int t;
    cin >> t ;
    while (t--){
        cin >> n >> m;
        for (int i = 0; i < m; ++i) cin >> a[i];
        ll sum = 0, lcm = 1;
        for (int i = 0; i < (1 << m); ++i){
            for(int j = 0; j < m; ++j){
                if (i & (1 << j)){
                    lcm = LCM(lcm, a[j]);
                }
            }
            int cnt = popcount(i);
            if (cnt & 1) sum += n / lcm;
            else sum -= n / lcm;
        }
        cout << sum << endl;
    }
    return 0;
}