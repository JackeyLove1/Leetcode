#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <climits>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <numeric>

using namespace std;

class Node {
public:
    int val;
    Node *next;
    Node *random;

    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    unordered_map<Node *, Node *> cache;

    Node *copyRandomList(Node *head) {
        if (head == nullptr) return nullptr;
        if (cache.count(head)) {
            return cache[head];
        }
        auto newHead = new Node(head->val);
        cache[head] = newHead;
        newHead->next = copyRandomList(head->next);
        newHead->random = copyRandomList(head->random);
        return newHead;
    }
};