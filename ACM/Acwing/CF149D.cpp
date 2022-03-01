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

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

constexpr int N = 720, MOD = 1000000007;
using ll = long long;
ll dp[N][N][3][3];
int match[N];
char s[N];
int n;
stack<int> st;

void dfs(int l, int r) {
    if (l + 1 == r) {
        dp[l][r][0][1] = dp[l][r][1][0] = 1;
        dp[l][r][0][2] = dp[l][r][2][0] = 1;
        // dp[l][r][0][0] = 1;
        return;
    }
    if (match[l] == r) {
        dfs(l + 1, r - 1);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (j != 1) dp[l][r][0][1] = (dp[l][r][0][1] + dp[l + 1][r - 1][i][j]) % MOD;
                if (j != 2) dp[l][r][0][2] = (dp[l][r][0][2] + dp[l + 1][r - 1][i][j]) % MOD;
                if (i != 1) dp[l][r][1][0] = (dp[l][r][1][0] + dp[l + 1][r - 1][i][j]) % MOD;
                if (i != 2) dp[l][r][2][0] = (dp[l][r][2][0] + dp[l + 1][r - 1][i][j]) % MOD;
                // dp[l][r][0][0] = (dp[l][r][0][0] + dp[l + 1][r - 1][i][j]) % MOD;
            }
        }
    } else {
        int match_l = match[l];
        dfs(l, match_l), dfs(match_l + 1, r);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int p = 0; p < 3; ++p) {
                    for (int q = 0; q < 3; ++q) {
                        if (j != p && ((i == 0) || (j == 0)) && ((p == 0) && (q == 0))) {
                            dp[l][r][i][q] = (dp[l][r][i][q] +
                                              dp[l][match_l][i][j] * dp[match_l + 1][r][p][q] % MOD) % MOD;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    fhj();
    cin >> s;
    n = strlen(s);
    for (int i = 0; i < n; ++i) {
        if (s[i] == '(') st.push(i);
        else match[st.top()] = i, match[i] = st.top(), st.pop();
    }
    dfs(0, n - 1);
    ll res = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            res = (res + dp[0][n - 1][i][j]) % MOD;
        }
    }
    cout << res << endl;
    return 0;
}