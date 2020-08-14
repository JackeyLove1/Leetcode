#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

ListNode *partition(ListNode *head, int x) {
    if (head == nullptr) return head;

    // 建立左右链表，左边的链表小于x，右边的链表大于x
    ListNode left_dummy(0);
    ListNode right_dummy(0);

    auto left_cur = &left_dummy;
    auto right_cur = &right_dummy;

    // 遍历链表
    for(; head != nullptr; head = head->next){
        ListNode *cur = new ListNode(head->val);
        if(head->val < x){
            left_cur->next = cur;
            left_cur = left_cur->next;
        }
        else{
            right_cur->next = cur;
            right_cur = right_cur->next;
        }
    }

    // 连接两个链表
    left_cur->next = right_dummy.next;
    right_cur->next = nullptr;
    return left_dummy.next;
}