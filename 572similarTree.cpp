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

bool judge(TreeNode *s, TreeNode *t) {
    if (s == nullptr && t == nullptr) return true;
    if (s != nullptr && t == nullptr) return false;
    if (s == nullptr && t != nullptr) return false;
    if (s->val == t->val)
        return judge(s->left, t->left) && judge(s->right, t->right);
    return false;
}

bool dfs(TreeNode *s, TreeNode *t) {
    if(s == nullptr) return false;
    return judge(s, t) || dfs(s->left, t) || dfs(s->right, t);
}

bool isSubtree(TreeNode *s, TreeNode *t) {
    return dfs(s, t);
}