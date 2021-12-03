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
    ListNode *oddEvenList(ListNode *head) {
        if (head == nullptr) return nullptr;
        vector<int> nodes;
        while (head != nullptr) {
            nodes.emplace_back(head->val);
            head = head->next;
        }
        auto dummy = new ListNode(-1, head);
        auto cur = dummy;
        for (int i = 0; i < nodes.size(); i += 2) {
            cur->next = new ListNode(nodes[i]);
            cur = cur->next;
        }
        for (int i = 1; i < nodes.size(); i += 2) {
            cur->next = new ListNode(nodes[i]);
            cur = cur->next;
        }
        return dummy->next;
    }
};
