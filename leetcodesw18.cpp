#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <unordered_map>
#include <unordered_set>
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
    ListNode *deleteNode(ListNode *head, int val) {
        if (head == nullptr) return nullptr;
        if (head->val == val) return head->next;
        auto dummy = new ListNode(-1, head);
        auto prev = dummy;
        while (head->val != val) {
            prev = prev->next;
            head = head->next;
        }
        prev->next = head->next;
        return dummy->next;
    }
};