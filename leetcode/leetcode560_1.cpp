#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <map>
#include <unordered_map>
#include <set>

using namespace std;

int subarraySum(vector<int> &nums, int k) {
    int n = nums.size();
    int ans = 0;
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        dp[i][i] = nums[i];
        if (dp[i][i] == k)
            ans++;
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            dp[i][j] = dp[i][j - 1] + nums[j];
            if (dp[i][j] == k)
                ans++;
        }
    }
    return ans;
}