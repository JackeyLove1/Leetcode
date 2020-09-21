#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
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

int sum = 0;
TreeNode *convertBST(TreeNode *root) {
    if(root == nullptr)
        return nullptr;
    convertBST(root->right);
    sum += root->val;
    root->val = sum;
    convertBST(root->left);
    return root;
}