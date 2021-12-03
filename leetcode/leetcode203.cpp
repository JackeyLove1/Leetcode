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
    ListNode *removeElements(ListNode *head, int val) {
        if (head == nullptr) return nullptr;
        // vector<ListNode*> nodes;
        auto dummy = new ListNode(-1, head);
        auto cur = dummy;
        while (head != nullptr) {
            if (head->val != val) {
                cur->next = head;
                cur = cur->next;
            }
            head = head->next;
        }
        cur->next = nullptr;
        return dummy->next;
    }
};