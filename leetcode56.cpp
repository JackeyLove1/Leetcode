#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <queue>
#include <set>
#include <stack>

using namespace std;

vector<vector<int>> merge(vector<vector<int>> &intervals) {
    if (intervals.empty()) return intervals;
    sort(intervals.begin(), intervals.end(), [](const vector<int> &v1, const vector<int> &v2) {
        if (v1[0] == v2[0]) {
            return v1[1] < v2[1];
        }
        return v1[0] < v2[0];
    });
    vector<vector<int>> res;
    int st = intervals[0][0], ed = intervals[0][1];
    for (auto &inter: intervals) {
        if (st <= inter[0] && inter[1] <= ed) {
            continue;
        } else if (ed < inter[0]) {
            res.push_back({st, ed});
            st = inter[0], ed = inter[1];
        } else {
            st = min(st, inter[0]);
            ed = max(ed, inter[1]);
        }
    }
    if (res.empty() || res.back()[1] < st) {
        res.push_back({st, ed});
    }
    return res;
}

