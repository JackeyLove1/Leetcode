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
ll dp[60][2][2]; // pos, cnt3, cnt8

ll dfs(int pos, bool cnt3, bool cnt8, bool limit) {
    if (pos == 0) return cnt3 || cnt8;
    auto &ret = dp[pos][cnt3][cnt8];
    if (!limit && ret != -1) return ret;
    int up = limit ? a[pos] : 9;
    ll ans = 0;
    for (int i = 0; i <= up; i++) {
        if (cnt3 && i == 8) continue;
        if (cnt8 && i == 3) continue;
        ans += dfs(pos - 1, cnt3 || i == 3, cnt8 || i == 8, limit && i == up);
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
    ll l, r;
    memset(dp, -1, sizeof dp);
    while (cin >> l >> r && l && r) {
        cout << solve(r) - solve(l - 1) << endl;
    }
    return 0;
}
