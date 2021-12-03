#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <deque>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

ListNode *rotateRight(ListNode *head, int k) {
    if (head == nullptr || k == 0) return head;
    ListNode *dummy = new ListNode(-1);
    dummy->next = head;

    // 使用deque的复杂方式
    deque<int> d;
    auto p = head;
    while (p != nullptr){
        d.push_back(p->val);
        p = p->next;
    }

    // 模拟操作
    k = k % d.size();
    while (k > 0){
        int tmp = d.back();
        d.pop_back();
        d.push_front(tmp);
        k--;
    }

    // 重塑链表
    while (!d.empty()){
        head = new ListNode(d.front());
        d.pop_front();
        head = head->next;
    }
    return dummy->next;
}
