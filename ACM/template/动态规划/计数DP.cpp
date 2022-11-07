#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <numeric>
#include <stack>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

inline int _count(int x) {
    return __builtin_popcount(x);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

using ll = long long;
int a[15], len;
ll dp[15][15];//pos, pre,

ll dfs(int pos, int pre, bool lead, bool limit) {
    if (pos > len) return 1;
    if (!limit && dp[pos][pre] != -1) return dp[pos][pre];
    ll ret = 0;
    int up = limit ? a[len - pos + 1] : 9;//当前位最大数字
    for (int i = 0; i <= up; i++)//从0枚举到最大数字
    {
        if (abs(i - pre) < 2) continue;
        if (lead && i == 0) ret += dfs(pos + 1, -2, 1, limit && i == up);
        else ret += dfs(pos + 1, i, 0, limit && i == up);
    }
    if (!limit && !lead) dp[pos][pre] = ret;
    return ret;
}

ll solve(ll x) {
    len = 0;
    while (x) {
        a[++len] = x % 10;
        x /= 10;
    }
    memset(dp, -1, sizeof dp);
    return dfs(1, -2, true, true);
}

ll l, r;

int main() {
    cin >> l >> r;
    cout << solve(r) - solve(l - 1) << endl;
    return 0;
}

/*
#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

static int f[11][10];
int a[20];

int dfs(int pos, int pre, bool limit) {
    if (pos == -1)return 1;
    int &v = f[pos][pre];
    if (!limit && v != -1) return v;
    int res = 0;
    int up = limit ? a[pos] : 9;
    for (int i = 0; i <= up; ++i) {
        res += dfs(pos - 1, i, limit && i == a[pos]);
    }
    if (!limit) v = res;
    return res;
}

int solve(int x) {
    if (!x) return 1;
    int pos = 0;
    memset(f, -1, sizeof f);
    while (x) {
        a[pos++] = x % 10;
        x /= 10;
    }
    return dfs(pos - 1, 0, 1);
}

int main() {
    fhj();
    int l, r;
    while (cin >> l >> r && l && r) {
        cout << solve(r) - solve(l - 1) << endl;
    }
    return 0;
}
*/