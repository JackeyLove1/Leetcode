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

inline int count(int state) {
    return __builtin_popcount(state);
}

class Solution {
public:
    int maxDiff(int num) {
        vector<int> nums;
        vector<int> res;
        while (num) {
            nums.push_back(num % 10);
            num /= 10;
        }
        vector<int> tmp;
        tmp.reserve(nums.size());
        reverse(nums.begin(), nums.end());
        std::function<int()> vec2num = [&]() -> int {
            int x = 0;
            for (const int n : tmp) {
                x = 10 * x + n;
            }
            return x;
        };
        // replace 0
        for (int i = 0; i < 10; ++i) {
            tmp.clear();
            for (int num : nums) {
                if (num == i) {
                    tmp.push_back(0);
                    continue;
                }
                tmp.push_back(num);
            }
            if (tmp.front() == 0) continue;
            res.push_back(vec2num());
        }
        // replace 1
        for (int i = 0; i < 10; ++i) {
            tmp.clear();
            for (int num : nums) {
                if (num == i) {
                    tmp.push_back(1);
                    continue;
                }
                tmp.push_back(num);
            }
            res.push_back(vec2num());
        }
        // replace 9
        for (int i = 0; i < 10; ++i) {
            tmp.clear();
            for (int num : nums) {
                if (num == i) {
                    tmp.push_back(9);
                    continue;
                }
                tmp.push_back(num);
            }
            res.push_back(vec2num());
        }
        int max_num = *max_element(res.begin(), res.end());
        int min_num = *min_element(res.begin(), res.end());
        return max_num - min_num;
    }
};