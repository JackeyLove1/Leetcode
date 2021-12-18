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
#include <cstring>
#include <cmath>

using namespace std;

template<typename T>
static inline void print(vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}


class Solution {
public:
    int majorityElement(vector<int> &nums) {
        unordered_map<int, int> m;
        int sz = nums.size() / 2;
        for (const int num : nums) {
            if (++m[num] > sz) {
                return num;
            }
        }
        return -1;
    }
};