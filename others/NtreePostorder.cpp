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

vector<int> res;

void traverse(Node *root) {
    if (root == nullptr) return;
    for(auto nodes : root->children){
        traverse(nodes);
    }
    res.push_back(root->val);
}

vector<int> postorder(Node *root) {
    traverse(root);
    return res;
}