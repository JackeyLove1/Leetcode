#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <cmath>

using namespace std;

vector<vector<int>> merge(vector<vector<int>> &intervals) {
    vector<vector<int>> res;
    if (intervals.empty()) return res;
    sort(intervals.begin(), intervals.end());
    res.push_back(intervals[0]);
    for (int i = 1; i < intervals.size(); i++) {
        // intervals don't coincide
        if(res.back()[1] < intervals[i][0])
            res.push_back(intervals[i]);
        else
            res.back()[1] = max(res.back()[1], intervals[i][1]);
    }
    return res;
}