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
    size_t getLength(ListNode *head) {
        int ret = 0;
        while (head) {
            head = head->next;
            ++ret;
        }
        return ret;
    }

    ListNode *getKthFromEnd(ListNode *head, int k) {
        int len = getLength(head);
        for (int i = 1; i < len - k + 1; i++) {
            head = head->next;
        }
        return head;
    }
};