#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <numeric>
#include <cmath>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    int numRollsToTarget(int d, int f, int target) {
        constexpr int MOD = 1e9 + 7;
        vector<vector<int>> dp(d + 2, vector<int>(target + 2, 0));
        dp[0][0] = 1;
        for (int i = 1; i <= d; i++) {
            for (int j = 0; j <= target; j++) {
                // dp[i][j] = dp[i - 1][j];
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

int main() {
    auto s = Solution();
    cout << s.numRollsToTarget(1, 6, 3) << " res: 1" << endl;
    cout << s.numRollsToTarget(2, 6, 3) << " res: 6" << endl;
    cout << s.numRollsToTarget(2, 5, 10) << " res: 1" << endl;
    cout << s.numRollsToTarget(30, 30, 500) << " res: 222616187" << endl;
    return 0;
}