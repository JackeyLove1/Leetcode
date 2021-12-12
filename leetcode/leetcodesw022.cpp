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
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        if(head == nullptr) return nullptr;
        auto p = head;
        int len = 0;
        while (p != nullptr) {
            ++len;
            p = p->next;
        }
        if(n == len){
            return head->next;
        }
        int m = len - n - 1;
        p = head;
        while (m--){
            p = p->next;
        }
        p->next = p->next->next;
        return head;
    }
};

int main(){

}