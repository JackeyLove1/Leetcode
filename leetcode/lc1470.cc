class Solution {
public:
    vector<int> shuffle(vector<int>& nums, int n) {
        vector<int> res;
        res.reserve(nums.size());
        for (int i = 0, j = n; j < nums.size(); ++i, ++j){
            res.emplace_back(nums[i]);
            res.emplace_back(nums[j]);
        }
        return res;
    }
};