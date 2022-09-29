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
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <functional>
#include <tuple>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using PII = pair<int, int>;


static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e5 + 100, M = 65, INF = 0x3f3f3f3f, MOD = 1e4;

int a[20];
ll dp[12][13][10][2];

ll dfs(int pos, int mod, int pre, int have13, bool limit) {
    if (pos == 0) return have13 && mod == 0;
    auto &ret = dp[pos][mod][pre][have13];
    if (!limit && ret != -1) return ret;
    int up = limit ? a[pos] : 9;
    ll ans = 0;
    for (int i = 0; i <= up; i++) {
        if (pre == 1 && i == 3) ans += dfs(pos - 1, (mod * 10 + i) % 13, i, 1, limit && i == up);
        else ans += dfs(pos - 1, (mod * 10 + i) % 13, i, have13, limit && i == up);
    }
    if (!limit) ret = ans;
    return ans;
}

ll solve(ll x) {
    int pos = 0;
    while (x) {
        a[++pos] = x % 10;
        x /= 10;
    }
    return dfs(pos, 0, 0, 0, 1);
}

int main() {
    ll l;
    memset(dp, -1, sizeof dp);
    while (~scanf("%lld", &l) && l) {
        printf("%lld\n", solve(l));
    };
    return 0;
}
