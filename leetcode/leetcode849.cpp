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
    int maxDistToClosest(vector<int> &seats) {
        int res = 0, n = seats.size();
        vector<int> onesIndex;
        for (int index = 0; index < n; ++index) {
            if (seats[index])onesIndex.push_back(index);
        }
        if (onesIndex.size() == 1) {
            return max(onesIndex[0], n - 1 - onesIndex[0]);
        }
        if (onesIndex.size() == n - 1) {
            return 1;
        }
        res = max(onesIndex.front(), n - 1 - onesIndex.back());
        for (int l = 0, r = 1; r < onesIndex.size(); ++l, ++r) {
            int diff = onesIndex[r] - onesIndex[l];
            if (diff % 2) res = max(res, (diff - 1) / 2);
            else res = max(res, diff / 2);
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> nums = {0, 0, 1, 0, 1, 1};
    cout << s.maxDistToClosest(nums) << endl;
}