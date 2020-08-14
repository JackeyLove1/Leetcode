#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <cmath>

using namespace std;

int maxSubArray(vector<int> &nums) {
    if (nums.empty()) return 0;
    int res = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        nums[i] = max(nums[i], nums[i] + nums[i - 1]);
        res = max(res, nums[i]);
    }
    return res;
}