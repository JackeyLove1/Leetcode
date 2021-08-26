#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <unordered_map>
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
    ListNode *deleteDuplicates(ListNode *head) {
        vector<int> nums;
        unordered_map<int, int>cnt;
        auto cur = head;
        while (cur != nullptr) {
            nums.push_back(cur->val);
            ++cnt[cur->val];
            cur = cur->next;
        }
        nums.erase(unique(nums.begin(), nums.end()), nums.end());
        auto dummy = new ListNode(-1);
        head = dummy;
        for (auto &num : nums) {
            if(cnt[num] > 1) continue;
            head->next = new ListNode(num);
            head = head->next;
        }
        return dummy->next;
    }
};