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

bool isPalindrome(ListNode *head) {
    // using vector
    if (head == nullptr) return true;
    vector<int> vec;
    while (head != nullptr) {
        vec.push_back(head->val);
        head = head->next;
    }
    size_t s = vec.size();
    for (int i = 0; i <= s/2;i++){
        if(vec[i] != vec[s-i-1])
            return false;
    }
    return true;
}