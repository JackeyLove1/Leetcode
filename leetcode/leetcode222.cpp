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

void dfs(TreeNode *root, int &cnt) {
    if (root == nullptr) return;
    cnt++;
    dfs(root->right, cnt);
    dfs(root->left, cnt);
}

int countNodes(TreeNode *root) {
    int cnt = 0;
    dfs(root, cnt);
    return cnt;
}