class Solution {
public:
    vector<int> missingTwo(vector<int> &nums) {
        unordered_map<int, bool> m;
        for (auto &num : nums) {
            m[num] = true;
        }
        vector<int> res;
        for (int i = 1; i <= nums.size() + 2; ++i) {
            if (!m.count(i)) res.push_back(i);
        }
        return res;
    }
};