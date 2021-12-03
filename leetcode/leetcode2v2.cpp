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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode *ret = new ListNode(-1);
        ListNode *pre = ret;
        int carry = 0;
        while (l1 || l2) {
            int a = l1 == nullptr ? 0 : l1->val;
            int b = l2 == nullptr ? 0 : l2->val;
            int sum = carry + a + b;
            pre->next = new ListNode(sum % 10);
            pre = pre->next;
            carry = sum / 10;
            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;
        }
        if (carry) {
            pre->next = new ListNode(carry);
        }
        return ret->next;
    }
};