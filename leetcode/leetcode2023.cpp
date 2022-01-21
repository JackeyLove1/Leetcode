class Solution {
public:
    int numOfPairs(const vector<string> &nums, const string &target) {
        int res = 0;
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j < nums.size(); ++j) {
                if (i == j) continue;
                if (nums[i].size() + nums[j].size() == target.size()) {
                    auto str = nums[i] + nums[j];
                    if (target == str) {
                        ++res;
                    }
                }
            }
        }
        return res;
    }
};