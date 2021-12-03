class Solution 
{
public:
    ListNode* removeZeroSumSublists(ListNode* head) 
    {
        unordered_map<int, ListNode*> presum_lastNode_dic;  //等于这个前缀和的最右一个的结点
        ListNode * dummy = new ListNode(0);
        dummy->next = head;
        ListNode* p = dummy;
        int cur_sum = 0;
        while (p)
        {
            cur_sum += p->val;
            presum_lastNode_dic[cur_sum] = p;           //初始化字典（map）
            p = p->next;
        }

        p = dummy;
        cur_sum = 0;
        while (p)
        {
            cur_sum += p->val;
            p->next = presum_lastNode_dic[cur_sum] -> next; //2个点的presum相同====中间数字和为0  或者只有自己1个点
            p = p->next;
        }

        return dummy->next;
    }
};

