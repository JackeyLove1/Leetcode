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
    vector<int> largestDivisibleSubset(vector<int> &nums) {
        if (nums.empty()) return {};
        sort(nums.begin(), nums.end());
        int n = nums.size();
        using PII = pair<int, int>;
        vector<int> f(n + 1, 1);
        int maxLen = 1, maxIndex = 0, preIndex = -1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                // cout << "nums[i]: " << nums[i] << " nums[j]: " << nums[j] << endl;
                if (nums[i] % nums[j] == 0) {
                    f[i] = max(f[i], f[j] + 1);
                    if (f[i] > maxLen) {
                        maxLen = f[i], maxIndex = i, preIndex = j;
                        // cout << "maxIndex: " << maxIndex << " value: " << nums[maxIndex] << " len: " << maxLen << endl;
                    }
                }
            }
        }
        // cout << "maxIndex: " << maxIndex << " value: " << nums[maxIndex] << endl;
        vector<int> res;
        res.reserve(n);
        int target1 = nums[maxIndex];
        res.push_back(target1);
        if (preIndex != -1) {
            int target2 = nums[preIndex];
            for (int i = preIndex; i >= 0; i--) {
                bool flag = true;
                for (auto &num : res) {
                    if (num % nums[i] != 0) {
                        flag = false;
                        break;
                    }
                }
                if (flag) res.push_back(nums[i]);
            }
        } else {
            return res;
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

int main() {
    vector<int> nums = {1, 2, 4, 8};
    auto s = Solution();
    auto res = s.largestDivisibleSubset(nums);
    print(res);
    vector<int> nums1 = {1, 2, 3};
    auto res1 = s.largestDivisibleSubset(nums1);
    print(res1);
    vector<int> nums2 = {4, 8, 10, 240};
    auto res2 = s.largestDivisibleSubset(nums2);
    print(res2);
    return 0;
}