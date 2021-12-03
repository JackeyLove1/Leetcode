#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <unordered_map>
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
    ListNode *partition(ListNode *head, int x) {
        auto leftHead = new ListNode(-1), rightHead = new ListNode(-1);
        auto lp = leftHead, rp = rightHead;
        while (head != nullptr) {
            if (head->val < x) {
                lp->next = new ListNode(head->val);
                lp = lp->next;
            } else {
                rp->next = new ListNode(head->val);
                rp = rp->next;
            }
            head = head->next;
        }

        lp->next = rightHead->next;
        return leftHead->next;
    }
};