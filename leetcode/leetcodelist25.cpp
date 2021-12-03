#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <climits>
#include <functional>
#include <unordered_set>
#include <numeric>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        auto dummy = new ListNode(-1);
        auto curr = dummy;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val < l2->val) {
                curr->next = l1;
                l1 = l1->next;
            } else {
                curr->next = l2;
                l2 = l2->next;
            }
            curr = curr->next;
        }
        while (l1 != nullptr) {
            curr->next = l1;
            curr = curr->next;
            l1 = l1->next;
        }
        while (l2 != nullptr) {
            curr->next = l2;
            curr = curr->next;
            l2 = l2->next;
        }
        return dummy->next;
    }
};