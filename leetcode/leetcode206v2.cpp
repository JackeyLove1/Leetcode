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
    ListNode *reverseList1(ListNode *head) {
        if (head == nullptr || head->next == nullptr)
            return head;
        auto newhead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return newhead;
    }

    ListNode *reverseList(ListNode *head) {
        if (head == nullptr || head->next == nullptr)
            return head;
        ListNode *pre = nullptr;
        auto cur = head;
        while (cur){
            auto next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
    }
};