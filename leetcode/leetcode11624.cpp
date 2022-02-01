#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    vector<vector<int>> pairSums(vector<int> &nums, int target) {
        sort(nums.begin(), nums.end());
        int l = 0, r = nums.size() - 1;
        vector<vector<int>> res;
        while (l < r) {
            int tmp = nums[l] + nums[r];
            if (tmp == target) {
                res.push_back({nums[l], nums[r]});
                ++l;
                --r;
            } else if (tmp > target) {
                --r;
            } else {
                ++l;
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> nums = {-2, -1, 0, 3, 5, 6, 7, 9, 13, 14};
    auto res1 = s.pairSums(nums, 12);
    for (const auto &num : res1) {
        print(num);
    }
}