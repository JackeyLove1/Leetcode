#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <functional>
#include <map>
#include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void traverse(TreeNode *root, unordered_map<int, int> &hash, int &maxCnt) {
    if (root == nullptr)
        return;
    hash[root->val]++;
    maxCnt = max(maxCnt, hash[root->val]);
    traverse(root->left, hash, maxCnt);
    traverse(root->right, hash, maxCnt);
}

vector<int> findMode(TreeNode *root) {
    vector<int> res;
    if (root == nullptr)
        return res;
    unordered_map<int, int> hash;
    int maxCnt = 0;
    traverse(root, hash, maxCnt);
    for (auto[k, v] : hash) {
        if (v == maxCnt)
            res.push_back(k);
    }
    return res;
}