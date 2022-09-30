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
ll dp[25][25];

ll dfs(int pos, int pre, bool limit) {
    if (pos == 0) return 1;
    auto &ret = dp[pos][pre];
    if (!limit && ret != -1) return ret;
    int up = limit ? a[pos] : 9;
    ll ans = 0;
    for (int i = 0; i <= up; i++) {
        if (std::abs(i - pre) >= 2) ans += dfs(pos - 1, i, limit && i == up);
        // cout << "i: " << i << " pos: " << pos << " pre: " << pre << " lim: " << limit << " ans: " << ans << endl;
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
    return dfs(pos, -2, 1);
}

int main() {
    fhj();
    ll l, r;
    memset(dp, -1, sizeof dp);
    while (cin >> l >> r && l && r) {
        cout << solve(r) - solve(l - 1) << endl;
    }
    solve(10);
    return 0;
}
