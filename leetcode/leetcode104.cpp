#include <iostream>
#include <utility>
#include <future>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}


class Solution {
public:
    int combinationSum4(vector<int> &nums, int target) {
        int res = 0;
        std::function<void(int)> dfs = [&](int sub_sum) {
            if (sub_sum > target) return;
            if (sub_sum == target) {
                ++res;
                return;
            }
            for (int num : nums) {
                dfs(sub_sum + num);
            }
        };
        dfs(0);
        return res;
    }
};

class Solution2 {
public:
    int combinationSum4(vector<int> &nums, int target) {
        sort(nums.begin(), nums.end());
        unordered_map<int, int> m;
        function<int(int)> dfs = [&](int cur) -> int {
            if (cur == 0) return 1;
            if (m.count(cur)) return m[cur];
            int &v = m[cur] = 0;
            for (auto &num : nums) {
                if (num <= cur) v += dfs(cur - num);
            }
            return v;
        };
        return dfs(target);
    }
};

int main() {
    vector<int> v1 = {1, 2, 3};
    Solution s;
    cout << s.combinationSum4(v1, 4) << " res: 7" << endl;
    cout << s.combinationSum4(v1, 32) << " res: ?" << endl;
}