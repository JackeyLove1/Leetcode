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
    TreeNode *left, *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

bool traverse(TreeNode *root, int val) {
    if (root == nullptr)
        return true;
    if (root->val != val)
        return false;
    return traverse(root->left, val) && traverse(root->right, val);
}

bool isUnivalTree(TreeNode *root) {
    if (root == nullptr)
        return true;
    int val = root->val;
    return traverse(root, val);
}