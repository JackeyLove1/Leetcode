#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <functional>
#include <map>
#include <unordered_map>
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

void traverse(TreeNode *root, vector<int> &record) {
    if (root == nullptr)
        return;
    traverse(root->left, record);
    record.push_back(root->val);
    traverse(root->right, record);
}

void hashfy(vector<int> &record, unordered_map<int, int> &hash) {
    set<int> s(record.begin(), record.end());
    for (int i = 0; i < record.size(); i++) {
        if (hash.find(record[i]) == hash.end()) {
            hash[record[i]] = record[i];
            for (auto num : s) {
                if (num > record[i])
                    hash[record[i]] += num;
            }
        }
    }
}

void helper(TreeNode *root, unordered_map<int, int> &hash) {
    if (root == nullptr)
        return ;
    root->val = hash[root->val];
    helper(root->left, hash);
    helper(root->right, hash);
}

TreeNode *convertBST(TreeNode *root) {
    vector<int> record;
    unordered_map<int, int> hash;
    traverse(root, record);
    hashfy(record, hash);
    helper(root, hash);
    return root;
}