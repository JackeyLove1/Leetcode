#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

template<typename T>
inline void print1(vector<T> &nums) {
    for (auto &num : nums) cout << num << " ";
    cout << endl;
}

class Solution {
    static constexpr int MOD = 1e9 + 7;

public:
    int numRollsToTarget(int d, int f, int target) {
        vector<vector<int>> dp(d + 1, vector<int>(target + 1, 0));
        dp[0][0] = 1;
        for (int i = 1; i <= d; i++) {
            for (int j = 0; j <= target; j++) {
                for (int k = 1; k <= f; k++) {
                    if (j >= k) {
                        dp[i][j] = (dp[i][j] + dp[i - 1][j - k]) % MOD;
                    }
                }
            }
        }
        return dp[d][target];
    }
};