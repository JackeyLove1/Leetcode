#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int traverse(TreeNode *root, TreeNode *child) {
    if (child == nullptr)
        return 0;
    return max(abs(root->val - child->val), max(traverse(root, child->left), traverse(root, child->right)));
}

int maxNode(TreeNode *root) {
    if (root == nullptr || (root->left == nullptr && root->right == nullptr))
        return 0;
    return max(traverse(root, root->left), traverse(root, root->right));
}

void getRes(TreeNode *root, int &res) {
    if (root == nullptr) return;
    res = max(res, maxNode(root));
    getRes(root->left, res);
    getRes(root->right, res);
}

int maxAncestorDiff(TreeNode *root) {
    int res = 0;
    getRes(root, res);
    return res;
}