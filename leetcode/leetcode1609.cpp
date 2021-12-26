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
    TreeNode *right, *left;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int val_) : val(val_), left(nullptr), right(nullptr) {}

};

class Solution {
public:
    bool isEvenOddTree(TreeNode *root) {
        vector<vector<int>> nums;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            int sz = q.size();
            vector<int> tmp;
            for (int i = 0; i < sz; ++i) {
                auto t = q.front();
                q.pop();
                tmp.push_back(t->val);
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
            nums.emplace_back(tmp);
        }
        // judge increment
        std::function<bool(vector<int> &, int)> check = [](vector<int> &num, int flag) -> bool {
            if (num[0] % 2 != flag) return false;
            for (int i = 0; i < num.size() - 1; ++i) {
                if (num[i + 1] % 2 != flag || num[i] % 2 != flag) return false;
                if (num[i + 1] <= num[i]) return false;
            }
            return true;
        };
        for (int i = 0; i < nums.size(); ++i) {
            if (i % 2 == 0) { // even increment
                if (!check(nums[i], 1)) return false;
            } else { // odd increment
                reverse(nums[i].begin(), nums[i].end());
                if (!check(nums[i], 0)) return false;
            }
        }
        return true;
    }
};