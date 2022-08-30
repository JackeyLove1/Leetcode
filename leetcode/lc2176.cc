class Solution {
public:
    int countPairs(vector<int> &nums, int k) {
        int res = 0;
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = i + 1; j < nums.size(); ++j) {
                if (nums[i] == nums[j] && i * j % k == 0) ++res;
            }
        }
        return res;
    }
};