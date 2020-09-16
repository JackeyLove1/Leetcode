#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void traverse(TreeNode *root, int level, map<int, int> &hash, int &depth) {
    if (root == nullptr)
        return;
    if (hash.find(level) == hash.end())
        hash[level] = root->val;
    else
        hash[level] = (hash[level] > root->val) ? hash[level] : root->val;
    depth = max(depth, level);
    traverse(root->left, level + 1, hash, depth);
    traverse(root->right, level + 1, hash, depth);
}

vector<int> largestValues(TreeNode *root) {
    vector<int> res;
    if(root == nullptr)
        return res;
    map<int, int> hash;
    int level = 0;
    int depth = 0;
    traverse(root, level, hash, depth);
    for (int i = 0; i <= depth; i++) {
        res.push_back(hash[i]);
    }
    return res;
}