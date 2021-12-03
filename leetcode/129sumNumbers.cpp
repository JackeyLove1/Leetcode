#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <deque>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

int dfs(TreeNode* root, int sum){
    if(root == nullptr) return sum;
    if(root != nullptr && root->left == nullptr && root->right == nullptr)
        return sum*10 + root->val;
    if(root != nullptr && root->left != nullptr && root->right == nullptr)
        return dfs(root->left, sum*10+root->val);
    if(root != nullptr && root->left == nullptr && root->right != nullptr)
        return dfs(root->right, sum*10+root->val);
    return dfs(root->right, sum*10+root->val) + dfs(root->left, sum*10+root->val);
}
int sumNumbers(TreeNode* root) {
    return dfs(root, 0);
}