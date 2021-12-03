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
    vector<int> frequencySort(vector<int> &nums) {
        unordered_map<int, int> m;
        for (auto &num : nums) {
            ++m[num];
        }
        sort(nums.begin(), nums.end(), [&m](const int x, const int y) {
            return m[x] == m[y] ? x > y : m[x] < m[y];
        });
        return nums;
    }
};