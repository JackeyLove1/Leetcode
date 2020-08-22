#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
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


void traverse(TreeNode *root, int level, unordered_map<int, vector<double>> &hash, int &depth) {
    if (root == nullptr) return;
    if (hash.find(level) == hash.end()) {
        hash[level] = vector<double>();
    }
    hash[level].push_back(root->val);
    depth = max(depth, level);
    traverse(root->left, level + 1, hash, depth);
    traverse(root->right, level + 1, hash, depth);
}

vector<double> averageOfLevels(TreeNode *root) {
    unordered_map<int, vector<double>> hash;
    int level = 0;
    int depth = 0;
    traverse(root, level, hash, depth);
    vector<double> res;
    for (int i = 0; i <= depth; i++) {
        double sum = 0;
        for (auto num : hash[i]) {
            sum += num;
        }
        res.push_back(sum / hash[i].size());
    }
    return res;
}