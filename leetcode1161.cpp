#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
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

void traverse(TreeNode *root, int level, unordered_map<int, vector<int>> &hash) {
    if (root == nullptr)
        return;
    hash[level].push_back(root->val);
    traverse(root->left, level + 1, hash);
    traverse(root->right, level + 1, hash);
}

int sum(vector<int> v) {
    int res = 0;
    for (auto num : v)
        res += num;
    return res;
}

int maxLevelSum(TreeNode *root) {
    unordered_map<int, vector<int>> hash;
    int level = 1;
    traverse(root, level, hash);
    int res = 1;
    int maxSum = INT_MIN;
    for (auto[k, v] : hash) {
        int tmp = sum(v);
        if (tmp > maxSum) {
            maxSum = tmp;
            res = k;
        }
    }
    return res;
}