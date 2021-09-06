//
// Created by Jacky on 2021/9/5.
//

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * @param a ListNode类vector 指向这些数链的开头
     * @return ListNode类
     */
    int getLen(ListNode *head) {
        auto p = head;
        int len = 0;
        while (p != nullptr) {
            ++len;
            p = p->next;
        }
        return len;
    }

    ListNode *solve(vector<ListNode *> &a) {
        // write code here
        auto dummy = new ListNode(-1);
        auto curr = dummy;
        int maxn = 0;
        for (auto &l : a) {
            maxn = max(getLen(l), maxn);
        }
        for (int i = 0; i < maxn; ++i) {
            for (auto &l : a) {
                if (l != nullptr) {
                    curr->next = l;
                    l = l->next, curr = curr->next;
                }
            }
        }
        curr->next = nullptr;
        return dummy->next;
    }
};