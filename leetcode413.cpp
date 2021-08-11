#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

template<typename T>
inline void print1(vector<T> &nums) {
    for (auto &num : nums) cout << num << " ";
    cout << endl;
}

class Solution {
public:
    inline int count(int cnt) {
        return cnt * (cnt - 1) / 2;
    }

    int numberOfArithmeticSlices(vector<int> &nums) {
        if (nums.size() <= 1) return 0;
        int n = nums.size();
        vector<int> diff(n + 1, 1e4);
        int res = 0;
        int cnt = 1;
        for (int i = 1; i < nums.size(); i++) {
            diff[i] = nums[i] - nums[i - 1];
            // cout << "diff: " << diff[i] << endl;
            if (diff[i] == diff[i - 1]) {
                cnt++;
            } else {
                res += count(cnt);
                cnt = 1;
            }
            // cout << "res: " << res << " cnt: " << cnt << endl;
        }
        if (cnt) res += count(cnt);
        return res;
    }
};

int main() {
    auto s = Solution();
    vector<int> nums = {1, 2, 3, 4};
    cout << s.numberOfArithmeticSlices(nums) << endl;
    return 0;
}