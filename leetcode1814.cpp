//
// Created by Jacky on 2021/12/1.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>
#include <unordered_map>
#include <map>
#include <numeric>

using namespace std;

class Solution {
public:
    int countNicePairs(vector<int> &nums) {
        // vector<int> diffNumsVec;
        unordered_map<int, int> diffCountMap;
        for (auto &num : nums) {
            string rev_str = to_string(num);
            reverse(rev_str.begin(), rev_str.end());
            int rev_num = stoi(rev_str);
            // diffNumsVec.emplace_back(num - rev_num);
            ++diffCountMap[num - rev_num];
        }
        const int MOD = 1e9 + 7;
        long long res = 0;
        for (auto&[_, v] : diffCountMap) {
            auto count = static_cast<long long>(v);
            res = (res + (count * (count - 1) / 2) % MOD) % MOD;
        }
        return static_cast<int>(res);
    }
};