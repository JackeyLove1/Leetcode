#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <numeric>
#include <cmath>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

/*
class Solution {
public:
    // 暴力next_permutation
    vector<int> rearrangeArray(vector<int> &nums) {
        if (nums.size() <= 2) return nums;
        auto check = [&]() {
            for (int i = 1; i < nums.size() - 1; i++) {
                if (nums[i] == (nums[i - 1] + nums[i + 1]) / 2)
                    return false;
            }
            return true;
        };
        sort(nums.begin(), nums.end());
        do {
            if (check()) return nums;
        } while (next_permutation(nums.begin(), nums.end()));
        return {};
    }
};
*/

class Solution {
public:
    // 暴力next_permutation
    vector<int> rearrangeArray(vector<int> &nums) {
        if (nums.size() <= 2) return nums;
        sort(nums.begin(), nums.end());
        // 大小大小。。。排列
        int n = nums.size(), l = 0, r = n - 1;
        vector<int> res;
        while (l < r) {
            if (l < n && l < r) res.push_back(nums[l++]);
            if (r >= 0 && l < r) res.push_back(nums[r--]);
        }
        return res;
    }
};