#include <iostream>
#include <algorithm>
#include <vector>
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


TreeNode *insertIntoBST(TreeNode *root, int val) {
    if(root == nullptr)
        return new TreeNode(val);
    else if(root->val > val){
        root->left = insertIntoBST(root->left, val);
        return root;
    }else{
        root->right = insertIntoBST(root->right, val);
        return root;
    }
}