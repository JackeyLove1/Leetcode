#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// 最长上升子序列问题
int lengthOfLIS(int nums[], int n) {
    if (n == 0) return 0;
    vector<int> dp(n + 1, 1);
    int res = INT_MIN;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[j] > nums[i]) {
                dp[j] = max(dp[j], dp[i] + 1);
                res = max(dp[j], res);
            }
        }
    }
    return res;
}

// Test function
int main() {
    int nums[] = {10, 9, 2, 5, 3, 7, 101, 18};
    int n = sizeof(nums) / sizeof(int);
    cout << lengthOfLIS(nums, n) << endl;
    return 0;
}