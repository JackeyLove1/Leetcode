class Solution {
public:
    int minDifference(vector<int> &nums) {
        if (nums.size() <= 3) return 0;
        int n = nums.size();
        sort(nums.begin(), nums.end());
        // 1 left 3
        int res1 = abs(nums.back() - nums[3]);
        // 2 right 3
        int res2 = abs(nums[n - 4] - nums.front());
        // 3 left1 right2
        int res3 = abs(nums[n - 3] - nums[1]);
        // 4 left 2 right 1
        int res4 = abs(nums[n - 2] - nums[2]);
        return min({res1, res2, res3, res4});
    }
};