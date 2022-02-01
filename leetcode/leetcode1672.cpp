class Solution {
public:
    int maximumWealth(const vector<vector<int>> &accounts) {
        const int m = accounts.size(), n = accounts[0].size();
        int res = INT_MIN;
        for (int i = 0; i < m; ++i) {
            int tmp = 0;
            for (int j = 0; j < n; ++j) {
                tmp += accounts[i][j];
            }
            res = max(res, tmp);
        }
        return res;
    }
};