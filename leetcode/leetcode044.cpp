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
    vector<int> largestValues(TreeNode *root) {
        vector<int> res;
        vector<int> nums;
        queue<TreeNode *> q;
        if (root == nullptr) return res;
        q.push(root);
        while (!q.empty()) {
            int sz = q.size();
            nums.clear();
            for (int i = 0; i < sz; ++i) {
                auto t = q.front();
                q.pop();
                nums.push_back(t->val);
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
            if (!nums.empty()) {
                res.push_back(*max_element(nums.begin(), nums.end()));
            }
        }
        return res;
    }
};