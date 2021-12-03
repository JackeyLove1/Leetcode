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
    ListNode *reverseBetween(ListNode *head, int left, int right) {
        if (head->next == nullptr) return head;
        vector<int> nums;
        auto cur = head;
        while (cur != nullptr) {
            nums.push_back(cur->val);
            cur = cur->next;
        }
        // auto l = lower_bound(nums.begin(), nums.end(), left);
        // auto r = upper_bound(nums.begin(), nums.end(), right);
//        int l = 0, r = nums.size() - 1;
//        while (l < r) {
//            while (l < r && nums[l] != left) ++l;
//            while (l < r && nums[r] != right) --r;
//            if (l < r) {
//                swap(nums[l++], nums[r--]);
//            }
//        }
        reverse(nums.begin() + left - 1, nums.begin() + right);
        auto dummy = new ListNode(-1, head);
        for (auto &num : nums) {
            head->val = num;
            head = head->next;
        }
        return dummy->next;
    }
};