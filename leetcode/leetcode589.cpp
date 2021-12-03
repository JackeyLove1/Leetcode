#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <functional>

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
    vector<int> res;

    inline void dfs(Node *root) {
        if(root == nullptr)
            return ;
        res.push_back(root->val);
        for(auto & node : root->children){
            dfs(node);
        }
    }

public:
    vector<int> preorder(Node *root) {
        // res.clear();
        dfs(root);
        return res;
    }
};