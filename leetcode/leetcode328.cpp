#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <deque>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *oddEvenList(ListNode *head) {
    if (head == nullptr) return nullptr;
    vector<int> odd;
    vector<int> even;
    int cnt = 0;
    while (head != nullptr) {
        if (cnt % 2 == 0)
            even.push_back(head->val);
        else
            odd.push_back(head->val);
        cnt++;
        head = head->next;
    }
    auto head0 = new ListNode(0);
    auto dummy = head0;
    for (int i = 0; i < even.size(); i++) {
        ListNode* tmp = new ListNode(even[i]);
        head0->next = tmp;
        head0 = head0->next;
    }
    for (int i = 0; i < odd.size(); i++) {
        ListNode* tmp = new ListNode(odd[i]);
        head0->next = tmp;
        head0 = head0->next;
    }
    return dummy->next;
}