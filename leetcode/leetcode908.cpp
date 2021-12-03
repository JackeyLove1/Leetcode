class Solution {
public:
    int smallestRangeI(vector<int> &nums, int k) {
        int minn = nums[0], maxn = nums[0];
        for (int x: nums) {
            minn = min(minn, x);
            maxn = max(maxn, x);
        }
        return max(0, maxn - minn - 2 * k);
    }
};