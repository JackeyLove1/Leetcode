#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <utility>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <atomic>
#include <thread>

#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

inline int count(int state) {
    return __builtin_popcount(state);
}


class Solution {
private:
    vector<int> nums;
    int sz;
public:
    Solution(ListNode *head) {
        while (head != nullptr) {
            nums.push_back(head->val);
            head = head->next;
        }
        sz = nums.size();
    }

    int getRandom() {
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_int_distribution<int> distr(0, 100);
        return nums[distr(eng) % sz];
    }
};