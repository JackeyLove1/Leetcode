#include <iostream>
#include <utility>
#include <future>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;

class Solution {
    template<typename T>
    inline void print(vector<T> &v) {
        for_each(v.begin(), v.end(), [](T &t) { cout << t << ' '; });
        cout << endl;
    }

public:
    const static int debug = 1;

    // 将0当作划分点，然后分区间处理
    // 计算区间内负数的个数，使用前缀和的思想
    int getMaxLen(vector<int> &nums) {
        int size_ = nums.size();
        if(nums.size() == 1 && nums.front() < 0) return 0;
        // vector<int> postive(size_ + 10, 0);
        vector<int> negtive(size_ + 10, 0);

        // function find_max_sub_length
        // input: [begin_index, end_index]
        // output: max_sub_multiply_length
        std::function<int(vector<int> &)> solve_vector = [](vector<int> &v) -> int {
            // 左右并行，寻找第一个偶数对和第一个奇数对，然后返回最大长度
            int odd_res = 0, even_res = 0;
            for (int i = v.size() - 1; i >= 0; --i) {
                if (v[i] % 2 == 0) {
                    even_res = i + 1;
                    if (debug)cout << "even idx: " << i << " res: " << even_res << endl;
                    break;
                }
            }
            int l = 0, r = v.size() - 1;
            while (l < v.size() && v[l] % 2 == 0) ++l;
            while (r >= 0 && v[r] % 2 == 0) --r;
            if (l < r) odd_res = r - l;
            if (debug) cout << "l: " << l << " r: " << r << " odd_res: " << odd_res << endl;
            return max(odd_res, even_res);
        };

        std::function<int(int, int)> solve = [&](int b_index, int e_index) -> int {
            if (b_index > e_index) return 0;
            if(b_index == e_index && nums[b_index] > 0) return 1;
            negtive[b_index] = nums[b_index] < 0 ? 1 : 0;
            for (int i = b_index + 1; i <= e_index; ++i) {
                negtive[i] = nums[i] < 0 ? negtive[i - 1] + 1 : negtive[i - 1];
            }
            vector<int> vtmp(negtive.begin() + b_index, negtive.begin() + e_index + 1);
            if (debug) print(vtmp);
            auto s = solve_vector(vtmp);
            if (debug) cout << "begin: " << b_index << " end: " << e_index << " res: " << s << endl;
            return s;
        };

        vector<int> zeros;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == 0) zeros.push_back(i);
        }
        // print(zeros);
        int res = 0;
        if (!zeros.empty()) {
            res = solve(0, zeros[0] - 1);
            for (int i = 1; i < zeros.size(); ++i) {
                res = max(res, solve(zeros[i - 1] + 1, zeros[i] - 1));
            }
            res = max(res, solve(zeros.back() + 1, nums.size() - 1));
        } else {
            res = solve(0, nums.size() - 1);
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> v = {1, 2, 3, 5, -6, 4, 0, 10};
    cout << s.getMaxLen(v) << " res: 4" << endl;
    vector<int> v2 = {-1, 2};
    cout << s.getMaxLen(v2) << " res: 1" << endl;
    vector<int> v3 = {1, -2, -3, 4};
    cout << s.getMaxLen(v3) << " res: 4" << endl;
    vector<int> v4 = {0, 1, -2, -3, 4};
    cout << s.getMaxLen(v4) << " res: 4" << endl;
    vector<int> v5 = {0, 1, -2, -3, -4};
    cout << s.getMaxLen(v5) << " res: 3" << endl;
}