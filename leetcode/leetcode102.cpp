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
    vector<vector<int>> res;
public:
    vector<vector<int>> levelOrder(TreeNode *root) {
        if (root == nullptr) return res;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            int n = q.size();
            vector<int> tmp;
            for (int i = 0; i < n; i++) {
                auto t = q.front();
                q.pop();
                tmp.push_back(t->val);
                if (t->left) q.push(t->left);
                if (t->right)q.push(t->right);
            }
            res.emplace_back(tmp);
        }
        return res;
    }
};