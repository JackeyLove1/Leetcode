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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode *> s;
        while (headA != nullptr) {
            s.insert(headA);
            headA = headA->next;
        }
        while (headB != nullptr) {
            if (s.count(headB)) return headB;
            headB = headB->next;
        }
        return nullptr;
    }
};