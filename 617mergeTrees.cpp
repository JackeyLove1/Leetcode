#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
    if(t1 == nullptr) return t2;
    if(t2 == nullptr) return t1;
    TreeNode* tmp = new TreeNode(t1->val+t2->val);
    tmp->left = mergeTrees(t1->left, t2->left);
    tmp->right = mergeTrees(t1->right, t2->right);
    return tmp;
}