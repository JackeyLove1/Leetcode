#include <iostream>
#include <utility>
#include <future>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    int purchasePlans(vector<int> &nums, int target) {
        sort(nums.begin(), nums.end());
        using ll = long long int;
        constexpr ll MOD = 1e9 + 7;
        ll res = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] >= target) break;
            int target_num = target - nums[i];
            auto iter = upper_bound(nums.begin() + i + 1, nums.end(), target_num);
            int dis = distance(nums.begin() + i + 1, iter);
            // cout << "nums[i]: " << nums[i] << " index: " << iter - nums.begin() << " dis: " << dis << endl;
            res = (ll(dis) + res) % MOD;
        }
        return res;
    }
};

int main() {
    vector<int> nums = {2, 5, 3, 5};
    Solution s;
    cout << s.purchasePlans(nums, 6) << " res:1" << endl;
    vector<int> nums2 = {2, 2, 1, 9};
    cout << s.purchasePlans(nums2, 10) << " res:4" << endl;
}