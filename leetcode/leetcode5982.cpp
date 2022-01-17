class Solution {
public:
    // 倒过来遍历的背包问题
    // 悬垂线法
    long long mostPoints(const vector<vector<int>> &questions) {
        int sz = questions.size();
        using ll = long long;
        ll res = 0;
        vector<ll> f(sz + 10, 0);
        vector<ll> right(sz + 10, 0);
        for (int i = sz - 1; i >= 0; --i) {
            int score = questions[i][0];
            int skip = questions[i][1];
            f[i] = score;
            if (i + skip + 1 < sz) {
                f[i] += right[i + skip + 1];
            }
            right[i] = max(f[i], right[i + 1]);
            res = max(res, f[i]);
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<vector<int>> nums = {{21, 5},
                                {92, 3},
                                {74, 2},
                                {39, 4},
                                {58, 2},
                                {5,  5},
                                {49, 4},
                                {65, 3}};
    cout << s.mostPoints(nums) << " res: 157" << endl;
}