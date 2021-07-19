#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <functional>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Node {
public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node *> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
private:
    int maxSum = INT_MIN;

    int getMax(TreeNode *node) {
        if (node == nullptr) return 0;
        int left = max(getMax(node->left), 0);
        int right = max(getMax(node->right), 0);

        int pathSum = left + right + node->val;
        maxSum = max(maxSum, pathSum);
        return max(left, right) + node->val;
    }

public:

    int maxPathSum(TreeNode *root) {
        getMax(root);
        return maxSum;
    }
};