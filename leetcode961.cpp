//
// Created by Jacky on 2021/12/1.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>
#include <unordered_map>


using namespace std;

class Solution {
public:
    int repeatedNTimes(vector<int> &nums) {
        int n = nums.size() / 2;
        using freq = int;
        using num = int;
        unordered_map<num, freq> m;
        for (auto &num : nums) {
            if (++m[num] == n) {
                return num;
            }
        }
        return nums[0];
    }
};