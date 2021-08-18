#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <numeric>
#include <cmath>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    int deleteAndEarn(vector<int> &nums) {
        unordered_map<int, int> cnt;
        for (auto &num : nums) {
            cnt[num] += num;
        }
        sort(nums.begin(), nums.end());
        nums.erase(unique(nums.begin(), nums.end()), nums.end());
        int n = nums.size();
        int res = 0;
        // print(nums);
        vector<int> f(n + 1, 0);
        for (int i = 0; i < n; i++) {
            int cnt_i = cnt[nums[i]];
            f[i] = cnt_i;
            for (int j = 0; j < i; j++) {
                if (nums[i] != nums[j] + 1) {
                    f[i] = max(f[i], f[j] + cnt_i);
                }
                // cout << "i: " << i << " f[i]: " << f[i] << endl;
            }
            res = max(res, f[i]);
        }
        return res;
    }
};

int main() {
    auto s = Solution();
    vector<int> nums0 = {3, 4, 2};
    cout << s.deleteAndEarn(nums0) << " res: 6" << endl;
    vector<int> nums1 = {2, 2, 3, 3, 3, 4};
    cout << s.deleteAndEarn(nums1) << " res: 9" << endl;
    vector<int> nums2 = {1};
    cout << s.deleteAndEarn(nums2) << " res: 1" << endl;
    return 0;
}