#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Node {
public:
    int val;
    Node *next;
    Node *random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    unordered_map<Node *, Node *> m;

    Node *copyRandomList(Node *head) {
        if (head == nullptr) return nullptr;
        if (!m.count(head)) {
            auto newhead = new Node(head->val);
            m[head] = newhead;
            newhead->next = copyRandomList(head->next);
            newhead->random = copyRandomList(head->random);
        }
        return m[head];
    }
};