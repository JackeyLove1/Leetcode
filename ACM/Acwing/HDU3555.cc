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
ll dp[25][25][2];

ll dfs(int pos, int pre, bool have, bool limit) {
    if (pos == 0) return have;
    auto &ret = dp[pos][pre][have];
    if (!limit && ret != -1) return ret;
    int up = limit ? a[pos] : 9;
    ll ans = 0;
    for (int i = 0; i <= up; i++) {
        if (pre == 4 && i == 9) ans += dfs(pos - 1, i, true, limit && i == up);
        else ans += dfs(pos - 1, i, have, limit && i == up);
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
    return dfs(pos, 0, 0, 1);
}

int main() {
    int t;
    cin >> t;
    memset(dp, -1, sizeof dp);
    while (t--) {
        ll x;
        cin >> x;
        cout << solve(x) << endl;
    }
    return 0;
}
