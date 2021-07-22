#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <queue>
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

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) return l2;
        if (l2 == nullptr) return l1;
        ListNode* dummy = new ListNode(-1);
        auto pre = dummy;
        while (l1 != nullptr && l2 != nullptr){
            if (l1->val < l2->val){
                pre->next = l1;
                l1 = l1->next;
            }else{
                pre->next = l2;
                l2 = l2->next;
            }
            pre = pre->next;
        }
        while (l1 != nullptr) {
            pre->next = l1;
            pre = pre->next;
            l1 = l1->next;
        }
        while (l2 != nullptr){
            pre->next = l2;
            pre = pre->next;
            l2 = l2->next;
        }
        return dummy->next;
    }
};