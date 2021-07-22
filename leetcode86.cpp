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

ListNode *partition(ListNode *head, int x) {
    if (head == nullptr) return nullptr;
    ListNode *left = new ListNode(-1);
    auto leftPre = left;
    ListNode *right = new ListNode(-1);
    auto rightPre = right;
    while (head) {
        if (head->val < x) {
            leftPre->next = head;
            leftPre = leftPre->next;
        } else {
            rightPre->next = head;
            rightPre = rightPre->next;
        }
        head = head->next;
    }
    rightPre->next = nullptr;
    leftPre->next = right->next;
    return left->next;
}