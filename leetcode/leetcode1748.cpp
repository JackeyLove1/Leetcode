class Solution {
public:
    int sumOfUnique(const vector<int> &nums) {
        unordered_map<int, int> um;
        for (int num : nums) {
            um[num]++;
        }
        int res = 0;
        for (const auto&[k, v] : um) {
            if (v == 1) {
                res += k;
            }
        }
        return res;
    }
};