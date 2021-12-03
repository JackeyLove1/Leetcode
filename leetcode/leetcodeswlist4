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
    void print(ListNode *head) {
        auto p = head;
        while (p != nullptr) {
            cout << p->val << " ";
            p = p->next;
        }
        cout << endl;
    }

    ListNode *reverseList(ListNode *head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode *pre = nullptr;
        auto cur = head;
        while (cur != nullptr) {
            auto next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
    }

    ListNode *add(ListNode *l1, ListNode *l2) {
        auto dummy = new ListNode(-1);
        auto cur = dummy;
        int carry = 0;
        while (l1 != nullptr || l2 != nullptr) {
            int x = l1 == nullptr ? 0 : l1->val;
            int y = l2 == nullptr ? 0 : l2->val;
            if (l1 != nullptr) l1 = l1->next;
            if (l2 != nullptr) l2 = l2->next;
            cur->next = new ListNode((x + y + carry) % 10);
            carry = (x + y + carry) / 10;
            cur = cur->next;
        }
        if (carry) {
            cur->next = new ListNode(carry);
        }
        return dummy->next;
    }

    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        auto p1 = reverseList(l1), p2 = reverseList(l2);
        // print(p1);
        // print(p2);
        auto res = add(p1, p2);
        // print(res);
        res = reverseList(res);
        return res;
    }
};

