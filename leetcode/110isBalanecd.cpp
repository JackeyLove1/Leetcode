#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int height(TreeNode *root) {
    if (root == nullptr) return 0;
    return 1 + max(height(root->left),
                   height(root->right));
}

bool isBalanced(TreeNode *root) {
    if (root == nullptr) return true;
    return abs(height(root->right) - height(root->left)) <= 1
           && isBalanced(root->left)
           && isBalanced(root->right);
}