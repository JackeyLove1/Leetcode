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
    ListNode *swapPairs(ListNode *head) {
        if (head == nullptr) return head;
        auto dummy = new ListNode(0, head);
        auto p = head;
        while (p != nullptr && p->next != nullptr) {
            swap(p->val, p->next->val);
            p = p->next->next;
        }
        return dummy->next;
    }
};