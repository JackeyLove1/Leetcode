//
// Created by Jacky on 2021/12/1.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>


using namespace std;

class Solution {
public:
    vector<int> numOfBurgers(int tomatoSlices, int cheeseSlices) {
        int &t = tomatoSlices;
        int &c = cheeseSlices;
        if (t % 2 || (t / 2 < c) || (2 * c < t / 2)) return {};
        return {t / 2 - c, 2 * c - t / 2};
    }
};