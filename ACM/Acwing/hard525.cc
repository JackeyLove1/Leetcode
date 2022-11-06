#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int len;
    static constexpr int N = 1e5 + 10, MOD = 1e9 + 7;
    int dp[N][2][3];//pos, A, L
    int dfs(int pos, int A, int L) {
        if (pos > len) return 1;
        if (dp[pos][A][L] != -1) return dp[pos][A][L];
        int ret = 0;
        for (int i = 0; i <= 2; i++) {
            if (i == 0) {
                ret = (ret + dfs(pos + 1, A, 0)) % MOD;
            } else if (i == 1) {
                if (A + 1 >= 2) continue;
                ret = (ret + dfs(pos + 1, A + 1, 0)) % MOD;
            } else {
                if (L + 1 >= 3) continue;
                ret = (ret + dfs(pos + 1, A, L + 1)) % MOD;
            }
        }
        dp[pos][A][L] = ret % MOD;
        return dp[pos][A][L];
    }

    int checkRecord(int n) {
        len = n;
        memset(dp, -1, sizeof dp);
        return dfs(1, 0, 0);
    }
};

int main() {
    Solution s{};
    cout << s.checkRecord(2) << " res: 8" << endl;
    cout << s.checkRecord(10101) << " res: 183236316" << endl;
    return 0;
}