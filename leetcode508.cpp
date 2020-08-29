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

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

int traverse(TreeNode *root, unordered_map<int, int> &hash, int &cnt) {
    if (root == nullptr) return 0;
    root->val += traverse(root->left, hash, cnt) + traverse(root->right, hash, cnt);
    if (hash.find(root->val) == hash.end())
        hash[root->val] = 1;
    else
        hash[root->val]++;
    cnt = max(cnt, hash[root->val]);
    return root->val;
}

vector<int> findFrequentTreeSum(TreeNode *root) {
    unordered_map<int, int> hash;
    int cnt = 0;
    traverse(root, hash, cnt);
    vector<int> res;
    for(auto it = hash.begin(); it != hash.end(); ++it){
        if(it->second == cnt)
            res.push_back(it->first);
    }
    return res;
}