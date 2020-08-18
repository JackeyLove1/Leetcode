#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <deque>
#include <queue>

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

TreeNode *insertBST(int num, TreeNode *root) {
    if (root == nullptr)
        return new TreeNode(num);
    else if (num > root->val)
        return insertBST(num, root->right);
    else
        return insertBST(num, root->left);
}


template<typename RandomAccess>
TreeNode *buildBST(RandomAccess First, RandomAccess Last) {
    auto length = distance(First, Last);
    if (length <= 0) return nullptr;
    auto mid = First + (Last - First) / 2;
    TreeNode *tmp = new TreeNode(*mid);
    tmp->left = buildBST(First, mid);
    tmp->right = buildBST(mid + 1, Last);
    return tmp;
}

TreeNode *sortedListToBST(ListNode *head) {
    if (head == nullptr) return nullptr;
    vector<int> v;
    while (head != nullptr) {
        v.push_back(head->val);
        head = head->next;
    }
    return buildBST(v.begin(), v.end());
}