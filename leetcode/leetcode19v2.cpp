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
    int getLength(ListNode *head) {
        int res = 0;
        while (head) {
            ++res;
            head = head->next;
        }
        return res;
    }

    ListNode *removeNthFromEnd(ListNode *head, int n) {
        auto dummy = new ListNode(0, head);
        auto cur = dummy;
        int len = getLength(head);
        for (int i = 1; i < len - n + 1; i++) {
            cur = cur->next;
        }
        cur->next = cur->next->next;
        return dummy->next;
    }
};