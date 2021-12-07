#include <iostream>
#include <utility>
#include <future>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>
#include <map>


using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    int minSteps(string s, string t) {
        unordered_map<char, int> sm, tm;
        for (auto &ch : s) {
            ++sm[ch];
        }
        for (auto &ch : t) {
            ++tm[ch];
        }
        int same_count = 0;
        for (auto&[k, v] : sm) {
            same_count += min(v, tm[k]);
        }
        return s.size() - same_count;
    }
};

int main() {
    Solution s;
    cout << s.minSteps("leetcode", "practice") << " res: 5" << endl;
}