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


class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        vector<int> nums;
        while (head){
            nums.emplace_back(head->val);
            head = head->next;
        }
        reverse(nums.begin(), nums.end());
        return nums;
    }
};