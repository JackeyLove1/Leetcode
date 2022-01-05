#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
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

inline int _count(int state) {
    return __builtin_popcount(state);
}

class Solution {
public:
    int getLucky(string s, int k) {
        // vector<int> nums;
        string nums;
        for (const auto ch : s) {
            nums += to_string(ch - 'a' + 1);
        }
        while (k--) {
            int num = 0;
            for (const auto ch : nums) {
                num += ch - '0';
            }
            nums = to_string(num);
        }
        return stoi(nums);
    }
};