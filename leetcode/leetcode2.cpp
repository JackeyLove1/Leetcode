#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <functional>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

inline void print(vector<int> &nums) {
    for (auto &num : nums) cout << num << " ";
    // cout << "end..." << endl;
}

ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode *res = new ListNode(-1);
    ListNode *pre = res;
    auto pa = l1, pb = l2;
    int carry = 0;
    while (pa != nullptr || pb != nullptr) {
        int va = 0, vb = 0;
        if (pa != nullptr) {
            va = pa->val;
            pa = pa->next;
        }
        if (pb != nullptr) {
            vb = pb->val;
            pb = pb->next;
        }
        int vc = va + vb + carry;
        carry = vc / 10;
        vc = vc % 10;
        pre->next = new ListNode(vc);
        pre = pre->next;
    }
    if(carry) pre->next = new ListNode(1);
    return res->next;
}

int main() {

}
