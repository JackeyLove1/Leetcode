#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <functional>
#include <queue>
#include <set>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    vector<TreeNode *> q;

    void dfs(TreeNode *root) {
        if (root == nullptr)
            return;
        q.push_back(root);
        if (root->left) dfs(root->left);
        if (root->right) dfs(root->right);
    }

public:
    void flatten(TreeNode *root) {
        TreeNode *res = new TreeNode(-1);
        auto pre = res;
        dfs(root);
        for (auto &node : q) {
            node->left = nullptr;
            pre->right = node;
            pre = pre->right;
        }
        root = res->right;
    }
};