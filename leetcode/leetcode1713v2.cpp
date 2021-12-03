#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <numeric>
#include <cmath>
#include <queue>

using namespace std;

class Solution {
public:
    int minOperations(vector<int> &target, vector<int> &arr) {
        int m = target.size(),;
        unordered_map<int, int> pos;
        for (int i = 0; i < m; i++) pos[target[i]] = i;
        vector<int> d;
        for (auto &num : arr) {
            if (pos.count(num)) {
                int idx = pos[num];
                auto it = lower_bound(d.begin(), d.end(), idx);
                if (it != d.end()) {
                    *it = idx;
                } else {
                    d.push_back(idx);
                }
            }
        }
        return m - d.size();
    }
};