#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

ListNode *removeDuplicateNodes(ListNode *head) {
    if (head == nullptr || head->next == nullptr) return head;
    ListNode *dummy = new ListNode(-1);
    dummy->next = head;
    // unordered_set<int> hash;

    // 设置当前节点和前一个节点
    ListNode *pre = head;
    ListNode *cur = head->next;
    for(; head != nullptr; head = head->next){
        // 达到末尾节点
        if(cur == nullptr) return dummy->next;

        if(cur->val == pre->val){
            // 将cur节点删除
            pre->next = cur->next;
            cur = cur->next;
            pre = pre->next;
        }
        else{
            // 前进
            pre = cur;
            cur = cur->next;
        }
    }
    return dummy->next;
}