#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <queue>
#include <set>
#include <stack>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    unordered_map<ListNode *, int> um;
    while (headA) {
        um[headA]++;
        headA = headA->next;
    }
    while (headB) {
        if (um.count(headB)) {
            return headB;
        }
        headB = headB->next;
    }
    return nullptr;
}