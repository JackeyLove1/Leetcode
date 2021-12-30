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
#include <cstring>
#include <cstdlib>
#include <tuple>
#include <climits>

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
    TreeNode *left, *right;
    int val;

    TreeNode(int val_) : val(val_), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    unordered_set<int> s;

    int numColor(TreeNode *root) {
        std::function<void(TreeNode *)> dfs = [&](TreeNode *r) {
            if (r) {
                s.insert(root->val);
                numColor(root->left);
                numColor(root->right);
            }
        };

        dfs(root);
        return s.size();
    }
};