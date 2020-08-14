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

ListNode *rotateRight(ListNode *head, int k) {
    if (head == nullptr || k == 0) return head;
    // ListNode *dummy = new ListNode(-1);

    // 计算head的长度
    auto p = head;
    int len = 1;
    while (p->next) {
        len++;
        p = p->next;
    }
    // 首尾相连
    p->next = head;

    // 计算截断长度
    int distance = len - k % len;
    for (int i = 0; i < distance; i++) {
        p = p->next;
    }
    head = p->next; // 新的首节点
    p->next = nullptr;
    return head;
}
