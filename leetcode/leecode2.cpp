#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* dummy = new ListNode(0);
    ListNode* l3 = dummy;
    int carry = 0;
    while (l1 != NULL || l2 != NULL){
        int x = (l1 == NULL) ? 0 : l1->val;
        int y = (l2 == NULL) ? 0 : l2->val;
        int sum = x + y + carry;
        carry = sum / 10;
        l3->next = new ListNode(sum % 10);
        l3 = l3->next;
        if(l1) l1 = l1->next;
        if(l2) l2 = l2->next;
    }
    if(carry) l3->next = new ListNode(1);
    return dummy->next;
}