#include <iostream>
#include "Logger.h"

using namespace std;

#include <unordered_map>
#include <map>
#include <set>

class Solution {
public:
    vector<int> powerfulIntegers(int x, int y, int bound) {
        // 双指针
        vector<int> x_nums, y_nums;
        x_nums.push_back(1);
        y_nums.push_back(1);
        if (x != 1) {
            int pre = 1;
            while (pre * x <= bound) {
                pre = pre * x;
                x_nums.push_back(pre);
            }
        }
        if (y != 1) {
            int pre = 1;
            while (pre * y <= bound) {
                pre = pre * y;
                y_nums.push_back(pre);
            }
        }
        set<int> s;
        for (int x_num : x_nums) {
            for (int y_num : y_nums) {
                int x_y_sum = x_num + y_num;
                if (x_y_sum <= bound) {
                    s.insert(x_y_sum);
                }
            }
        }
        vector<int> res(s.begin(), s.end());
        return res;
    }
};