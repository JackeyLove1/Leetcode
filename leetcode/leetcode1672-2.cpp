class Solution {
public:
    int maximumWealth(vector<vector<int>> &accounts) {
        int res = INT_MIN;
        for (const auto &vec : accounts) {
            res = max(res, accumulate(vec.begin(), vec.end(), 0));
        }
        return res;
    }
};