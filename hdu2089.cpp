// Author: Jacky
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>
#include <numeric>


using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}


int n, m, a[7], dp[7][2][2];

int dfs(int pos, int pre, int lim) {
    if (pos == -1) return 1;
    if (dp[pos][pre][lim] != -1) return dp[pos][pre][lim];
    int ub = lim ? a[pos] : 9;
    int ans = 0;
    for (int i = 0; i <= ub; ++i) {
        if (i == 4) continue;
        else if (pre && i == 2) continue;
        ans += dfs(pos - 1, i == 6, lim && i == a[pos]);
    }
    dp[pos][pre][lim] = ans;
    return ans;
}

int solve(int x) {
    int cnt = 0;
    memset(dp, -1, sizeof dp);
    while (x) {
        a[cnt++] = x % 10;
        x /= 10;
    }
    return dfs(cnt - 1, 0, 1);
}

int main() {
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        cout << solve(m) - solve(n - 1) << "\n";
    }
}