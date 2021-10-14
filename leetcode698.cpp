class Solution {
public:
    bool canPartitionKSubsets(vector<int> &nums, int k) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int n = nums.size();
        if (sum % k != 0) return false;
        int target = sum / k;
        sort(nums.begin(), nums.end());
        if (nums.back() > target) return false;
        vector<bool> f(1 << n, false);
        f[0] = true;
        vector<int> cost(1 << n, 0);
        for (int i = 0; i < 1 << n; ++i) {
            if (!f[i]) continue;
            for (int j = 0; j < n; ++j) {
                if (i & (1 << j) != 0) {
                    continue;
                }
                auto next = i | (1 << j);
                if (f[next]) continue;
                if ((cost[i] % target) + nums[j] <= target) {
                    cost[next] = cost[i] + nums[j];
                    f[next] = true;
                } else {
                    break;
                }
            }
        }
        return f[(1 << n) - 1];
    }
};