#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <functional>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

int depth(TreeNode *root) {
    if (root == nullptr)
        return 0;
    if (root->right == nullptr && root->left == nullptr)
        return 1;
    return max(depth(root->left), depth(root->right)) + 1;
}

bool isBalanced(TreeNode *root) {
    if (root == nullptr)
        return true;
    if (root->left == nullptr && root->right == nullptr)
        return true;
    return abs(depth(root->left) - depth(root->right)) <= 1 &&
           isBalanced(root->left) && isBalanced(root->right);
}