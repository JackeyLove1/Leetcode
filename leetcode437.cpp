#include <iostream>
#include <regex>
#include <string>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

int count(TreeNode *node, int sum) {
    if (node == nullptr) return 0;
    return (node->val == sum) + count(node->left, sum - node->val)
           + count(node->right, sum - node->val);
}

int pathSum(TreeNode *root, int targetSum) {
    if (root == nullptr) return 0;
    return count(root, targetSum) + pathSum(root->right, targetSum)
           + pathSum(root->left, targetSum);
}