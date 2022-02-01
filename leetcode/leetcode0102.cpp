class Solution {
public:
    int findTargetSumWays(const vector<int> &nums, int target) {
        int res = 0;
        unordered_map<int, int> mp;
        std::function<void(int, int)> dfs1 = [&](int pos, int cur) {
            if (pos == nums.size() / 2) {
                mp[cur]++;
                return;
            }
            dfs1(pos + 1, cur + nums[pos]);
            dfs1(pos + 1, cur - nums[pos]);
        };
        dfs1(0, 0);
        std::function<void(int, int)> dfs2 = [&](int pos, int cur) {
            if (pos == nums.size()) {
                res += mp[target - cur];
                return;
            }
            dfs2(pos + 1, cur + nums[pos]);
            dfs2(pos + 1, cur - nums[pos]);
        };
        dfs2(nums.size() / 2, 0);
        return res;
    }
};