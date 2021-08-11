#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

template<typename T>
inline void print1(vector<T> &nums) {
    for (auto &num : nums) cout << num << " ";
    cout << endl;
}

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isHelper(TreeNode *left, TreeNode *right) {
        if (left == nullptr && right == nullptr) return true;
        if (left == nullptr || right == nullptr) return false;
        if (left->val != right->val) return false;
        return isHelper(left->left, right->right) && isHelper(left->right, right->left);
    }

    bool isSymmetric(TreeNode *root) {
        if (root == nullptr) return true;
        return isHelper(root->left, root->right);
    }
};