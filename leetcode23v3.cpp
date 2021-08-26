#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <cassert>

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
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode *dummy = new ListNode(-1);
        auto cur = dummy;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val < l2->val) {
                cur->next = l1;
                l1 = l1->next;
            } else {
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        while (l1 != nullptr) {
            cur->next = l1;
            cur = cur->next;
            l1 = l1->next;
        }

        while (l2 != nullptr) {
            cur->next = l2;
            cur = cur->next;
            l2 = l2->next;
        }

        return dummy->next;
    }

    ListNode *mergeKLists(vector<ListNode *> &lists) {
        if (lists.empty()) return nullptr;
        auto ret = lists[0];
        for (int i = 1; i < lists.size(); i++) {
            ret = mergeTwoLists(ret, lists[i]);
        }
        return ret;
    }
};
