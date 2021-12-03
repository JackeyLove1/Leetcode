#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <stack>

using namespace std;

bool canPartition(vector<int> &nums) {
    int sum = 0;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        sum += nums[i];
    }
    if (sum % 2 != 0) return false;
    sum = sum / 2;
    vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, false));
    for (int i = 0; i <= n; i++) {
        dp[i][0] = true;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            if (j < nums[i - 1])
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
        }
    }
    return dp[n][sum];
}