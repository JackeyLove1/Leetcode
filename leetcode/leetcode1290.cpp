#include <unordered_map>
#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>


using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    int getDecimalValue(ListNode *head) {
        vector<int> vec;
        while (head) {
            vec.push_back(head->val);
            head = head->next;
        }
        int res = 0, cur = 1;
        while (!vec.empty()) {
            if (vec.back() == 1) {
                res += cur;
            }
            vec.pop_back();
            cur <<= 1;
        }
        return res;
    }
};