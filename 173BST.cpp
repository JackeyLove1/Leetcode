#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <deque>
#include <queue>
#include <math.h>
#include <set>
#include <stack>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class BSTIterator {
public:
    vector<int> nums;
    TreeNode *root;
    int point;

    void traverse(TreeNode *root) {
        if (root == nullptr) return;
        traverse(root->left);
        nums.push_back(root->val);
        traverse(root->right);
    }

    BSTIterator(TreeNode *p) {
        root = p;
        point = -1;
        traverse(root);
    }

    /** @return the next smallest number */
    int next() {
        return nums[++point];
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return point + 1 < nums.size();
    }
};