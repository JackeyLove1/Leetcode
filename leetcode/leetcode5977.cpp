class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        int cnt = accumulate(nums.begin(), nums.end(), 0);
        if (cnt == 0) {
            return 0;
        }
        
        int cur = 0;
        for (int i = 0; i < cnt; ++i) {
            cur += (1 - nums[i]);
        }
        int ans = cur;
        for (int i = 1; i < n; ++i) {
            if (nums[i - 1] == 0) {
                --cur;
            }
            if (nums[(i + cnt - 1) % n] == 0) {
                ++cur;
            }
            ans = min(ans, cur);
        }
        return ans;
    }
};

