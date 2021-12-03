#include <iostream>
#include <algorithm>
#include <vector>
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

void traverse(TreeNode *root, int &sum) {
    if (root == nullptr)
        return;
    if (root->left != nullptr && root->left->left == nullptr && root->left->right == nullptr) {
        sum += root->left->val;
    }
    traverse(root->left, sum);
    traverse(root->right, sum);
}

int sumOfLeftLeaves(TreeNode *root) {
    int sum = 0;
    traverse(root, sum);
    return sum;
}