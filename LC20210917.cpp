// Author: Jacky
// Time: 2021-09-17
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

// LC442
class Solution442 {
public:
    vector<int> findDuplicates(vector<int> &nums) {
        vector<int> res;
        for (int i = 0; i < nums.size(); ++i) {
            int num = abs(nums[i]);
            nums[num - 1] *= -1;
            // print(nums);
            if (nums[num - 1] > 0) {
                res.push_back(num);
            }
        }
        return res;
    }
};

// LC46
class Solution46 {
public:
    vector<vector<int>> permute(vector<int> &nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        do {
            res.push_back(nums);
        } while (next_permutation(nums.begin(), nums.end()));
        return res;
    }
};

// LC142
struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

class Solution142 {
public:
    ListNode *detectCycle(ListNode *head) {
        if (head == nullptr || head->next == nullptr) return nullptr;
        auto fast = head, slow = head;
        while (fast) {
            fast = fast->next;
            if (fast == nullptr || fast->next == nullptr) return nullptr;
            fast = fast->next, slow = slow->next;
            if (fast == slow) break;
        }
        slow = head;
        while (slow != fast) {
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
};

// LC322
class Solution322 {
public:
    int coinChange(vector<int> &coins, int amount) {
        int n = coins.size();
        vector<int> f(amount + 10, 1e6);
        f[0] = 0;
        for (auto &coin : coins) {
            for (int j = coin; j <= amount; j++) {
                f[j] = min(f[j - coin] + 1, f[j]);
            }
        }
        return f[amount] == 1e6 ? -1 : f[amount];
    }
};

