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
    bool canPartition(vector<int> &nums) {
        if (nums.size() < 2) return false;
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int maxNum = *max_element(nums.begin(), nums.end());
        if (sum & 1) return false;
        int target = sum >> 1;
        if (maxNum > target) return false;
        vector<vector<bool>> f(nums.size() + 1, vector<bool>(target + 1, false));
        for (int i = 0; i < nums.size(); i++) {
            f[i][0] = true;
        }
        f[0][nums[0]] = true;
        for (int i = 1; i < nums.size(); i++) {
            for (int j = target; j >= 0; j--) {
                if (j >= nums[i]) {
                    f[i][j] = f[i][j] || f[i - 1][j - nums[i]];
                } else {
                    f[i][j] = f[i - 1][j];
                }
            }
        }
        return f[nums.size() - 1][target];
    }
};