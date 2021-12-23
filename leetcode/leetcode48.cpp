#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <cstring>
#include <cmath>
#include <list>
#include <atomic>

using namespace std;

template<typename T>
static inline void print(vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class TreeNode {
public:
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int val_) : val(val_), left(nullptr), right(nullptr) {}

};

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.empty()) return 0;
        int res = 1;
        unordered_map<int, int> m;
        int l = 0;
        s = static_cast<const string>(s);
        for (int r = 0; r < s.size(); ++r) {
            ++m[s[r]];
            while (m[s[r]] > 1 && l < r) {
                --m[s[l++]];
            }
            res = max(res, r - l + 1);
        }
        return res;
    }
};