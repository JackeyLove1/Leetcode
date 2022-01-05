class Solution {
public:
    int countNegatives(vector<vector<int>> &grid) {
        int cnt_ = 0;
        for (auto &vec : grid) {
            for (auto num : vec) {
                if (num < 0) ++cnt_;
            }
        }
        return cnt_;
    }
};

class Solution2{
public:
    int countNegatives(vector<vector<int>> &grid) {
        int cnt = 0;
        for_each(grid.begin(), grid.end(), [&](const vector<int> &vec) {
            for (const int num : vec) cnt = num < 0 ? cnt + 1 : cnt;
        });
        return cnt;
    }
};