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
    TreeNode *left, *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void levelTraverse(TreeNode* root, int level, unordered_map<TreeNode *, int>& hash, int& maxLevel){
    if (root == nullptr)
        return ;
    hash[root] = level;
    maxLevel = max(maxLevel, level);
    levelTraverse(root->left, level+1, hash, maxLevel);
    levelTraverse(root->right, level+1, hash, maxLevel);
}

int findBottomLeftValue(TreeNode *root) {
    unordered_map<TreeNode *, int> hash;
    int level = 1;
    int maxLevel = 1;
    levelTraverse(root, level, hash, maxLevel);
    // 使用层序遍历获得第一个maxLevel
    deque<TreeNode* > d;
    d.push_back(root);
    while (!d.empty()){
        auto tmp = d.front();
        d.pop_front();
        if(hash[tmp] == maxLevel)
            return tmp->val;
        else{
            if(tmp->left != nullptr)
                d.push_back(tmp->left);
            if(tmp->right != nullptr)
                d.push_back(tmp->right);
        }
    }
    return -1;
}