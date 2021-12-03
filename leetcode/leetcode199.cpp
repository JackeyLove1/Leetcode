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

int maxLevel = 0;

void traverseLevel(TreeNode *root, int level, unordered_map<TreeNode *, int> &hash) {
    if (root == nullptr) return;
    hash[root] = level;
    maxLevel = max(maxLevel, level);
    traverseLevel(root->left, level + 1, hash);
    traverseLevel(root->right, level + 1, hash);
}

void bfs(TreeNode *root, unordered_map<TreeNode *, int> &hash, unordered_map<int, vector<int>> &record) {
    if(root == nullptr) return ;
    deque<TreeNode*>d;
    d.push_back(root);
    while (!d.empty()){
        auto p = d.front();
        d.pop_front();
        if(record.find(hash[p]) == record.end())
            record[hash[p]] = {};
        record[hash[p]].push_back(p->val);
        if(p->left != nullptr) d.push_back(p->left);
        if(p->right != nullptr) d.push_back(p->right);
    }
}

vector<int> rightSideView(TreeNode *root) {
    if(root == nullptr) return {};
    unordered_map<TreeNode *, int> hash;
    unordered_map<int, vector<int>> record;
    int level = 0;
    traverseLevel(root, level, hash);
    bfs(root, hash, record);
    vector<int> res;
    for(int i = 0;i<=maxLevel;i++){
        res.push_back(record[i].back());
    }
    return res;
}