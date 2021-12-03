#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void dfs(vector<string> &paths, TreeNode *root, string path) {
    if (root == nullptr) {
        return;
    }
    if(root->left == nullptr && root->right == nullptr){
        paths.push_back(path);
    }
    if(root->left != nullptr){
        dfs(paths, root->left, path+"->"+to_string(root->left->val));
    }
    if(root->right != nullptr){
        dfs(paths, root->left, path+"->"+to_string(root->right->val));
    }
}

vector<string> binaryTreePaths(TreeNode *root) {
    vector<string> paths;
    if(root == nullptr)
        return paths;
    dfs(paths, root, to_string(root->val));
    return paths;
}