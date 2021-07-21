#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <queue>
#include <set>

using namespace std;

int minPairSum(vector<int> &nums) {
    if (nums.empty()) return 0;
    sort(nums.begin(), nums.end());
    int res = nums.front() + nums.back();
    for (int i = 0, j = nums.size() - 1; i < j; i++, j--) {
        res = max(res, nums[i] + nums[j]);
    }
    return res;
}