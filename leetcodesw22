#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <climits>
#include <functional>
#include <numeric>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        if(head == nullptr) return nullptr;
        auto p = head;
        while (k--){
            if(p == nullptr) return nullptr;
            p = p->next;
        }
        while (p != nullptr){
            head = head->next;
            p = p->next;
        }
        return head;
    }
};