#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <cstring>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    int minOperations(vector<int> &nums) {
        if (nums.size() == 1) return 0;
        int ops = 0, expected = nums[0] + 1;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] > expected) {
                expected = nums[i] + 1;
            } else if (nums[i] == expected) {
                ++expected;
            } else {
                ops += expected - nums[i];
                ++expected;
            }
        }
        return ops;
    }
};