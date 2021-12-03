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

ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    vector<int> nums1;
    vector<int> nums2;
    while (l1 != nullptr) {
        nums1.push_back(l1->val);
        l1 = l1->next;
    }
    while (l2 != nullptr) {
        nums2.push_back(l2->val);
        l2 = l2->next;
    }
    reverse(nums1.begin(), nums1.end());
    reverse(nums2.begin(), nums2.end());
    int carry = 0;
    int p = 0, m = nums1.size(), n = nums2.size();
    vector<int> nums3;
    while (p < m || p < n) {
        int x = (p < m) ? nums1[p] : 0;
        int y = (p < n) ? nums2[p] : 0;
        int tmp = x + y + carry;
        if (tmp < 10) {
            nums3.push_back(tmp);
            p++;
            carry = 0;
        } else {
            nums3.push_back(tmp - 10);
            p++;
            carry = 1;
        }
    }
    if(carry > 0) nums3.push_back(carry);
    reverse(nums3.begin(), nums3.end());
    ListNode *l3 = new ListNode(-1);
    auto dummy = l3;
    for (auto num : nums3) {
        ListNode *tmp = new ListNode(num);
        l3->next = tmp;
        l3 = l3->next;
    }
    return dummy->next;
}