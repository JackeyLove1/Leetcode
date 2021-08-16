#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <cmath>

using namespace std;

class Solution {
public:
    using PII = pair<int, int>;
    map<PII, int> cache;

    int findTargetSumWays(vector<int> &nums, int target) {
        cache.clear();
        return backtrack(nums, target, 0, 0);
    }

    int backtrack(vector<int> &nums, int target, int index, int sum) {
        auto p = make_pair(index, sum);
        if (cache.find(p) != cache.end()) return cache[p];
        cache[p] = 0;
        int &v = cache[p];
        if (index == nums.size()) {
            if (sum == target) {
                return v = 1;
            }
        } else {
            int left = backtrack(nums, target, index + 1, sum + nums[index]);
            int right = backtrack(nums, target, index + 1, sum - nums[index]);
            return v = left + right;
        }
        return 0;
    }
};


int main() {
    vector<int> nums = {1, 1, 1, 1, 1};
    int target = 3;
    auto s = Solution();
    cout << s.findTargetSumWays(nums, target) << " res: 5" << endl;
    vector<int> nums2 = {1};
    int target2 = 1;
    cout << s.findTargetSumWays(nums2, target2) << " res: 1" << endl;
    return 0;
}