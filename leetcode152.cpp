#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>

using namespace std;

typedef struct Node {
    int minNum;
    int maxNum;

    Node(int _minNum, int _maxNum) {
        minNum = _minNum;
        maxNum = _maxNum;
    }
} Node;

int maxProduct(vector<int> &nums) {
    if (nums.empty()) return 0;
    int n = nums.size();
    if(n == 1) return nums[0];
    Node tmp(INT_MAX, INT_MIN);
    vector<Node> dp(n, tmp);
    dp[0].maxNum = dp[0].minNum = nums[0];
    int res = nums[0];
    for (int i = 1; i < n; i++) {
        dp[i].maxNum = max(max(dp[i - 1].minNum * nums[i], dp[i - 1].maxNum * nums[i]), nums[i]);
        dp[i].minNum = min(min(dp[i - 1].minNum * nums[i], dp[i - 1].maxNum * nums[i]), nums[i]);
        res = max(res, dp[i].maxNum);
    }
    return res;
}

int main() {
    vector<int> nums = {-2, 0, -1};
    cout << maxProduct(nums) << endl;
    vector<int> nums1 = {2, 3, -2, 4};
    cout << maxProduct(nums1) << endl;
    vector<int> nums2 = {-2};
    cout << maxProduct(nums2) << endl;
}