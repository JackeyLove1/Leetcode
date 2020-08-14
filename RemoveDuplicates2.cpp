#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* deleteDuplicates(ListNode* head) {
    if(head == nullptr || head->next == nullptr) return head;
    ListNode *dummy = new ListNode(-1);
    dummy->next = head;
    unordered_map<int, int> hash;
    for(; head != nullptr; head = head->next){
        if(hash.find(head->val) == hash.end())
            hash[head->val] = 1;
        else
            hash[head->val]++;
    }
    auto pre = dummy;
    auto cur = dummy->next;
    while(cur != nullptr){
        if(hash[cur->val] > 1){
            // 删除该节点
            pre->next = cur->next;
            // pre = pre->next;
            cur = cur->next;
        }
        else{
            pre = pre->next;
            cur = cur->next;
        }
    }
    return dummy->next;
}