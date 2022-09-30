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

constexpr int N = 1e5 + 100, M = 65, INF = 0x3f3f3f3f, MOD = 10000007;

int a[60];
ll dp[60][60]; // pos, count

ll dfs(int pos, int cnt, bool limit) {
    if (pos == 0) return std::max(cnt, 1);
    auto &ret = dp[pos][cnt];
    if (!limit && ret != -1) return ret;
    int up = limit ? a[pos] : 1;
    ll ans = 1;
    for (int i = 0; i <= up; i++) {
        ans = (ans * (dfs(pos - 1, cnt + (i == 1), limit && i == up) % MOD)) % MOD;
        // cout << "pos: " << pos << " cnt: " << cnt << " up: " << up << " i: " << i << " ans: " << ans << endl;
    }
    if (!limit) ret = ans;
    return ans;
}

ll solve(ll x) {
    int pos = 0;
    while (x) {
        a[++pos] = x % 2;
        x /= 2;
    }
    return dfs(pos, 0, 1);
}

int main() {
    ll l;
    memset(dp, -1, sizeof dp);
    while (cin >> l && l) {
        cout << solve(l) << endl;
    }
    return 0;
}
