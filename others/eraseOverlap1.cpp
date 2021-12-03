#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

static bool cmp(vector<int> &v1, vector<int> &v2) {
    return v1[1] < v2[1];
}

int eraseOverlapIntervals(vector<vector<int>> &intervals) {
    if (intervals.empty()) return 0;
    sort(intervals.begin(), intervals.end(), cmp);
    int start = intervals[0][0], end = intervals[0][1];
    int count = 1;
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] >= end) {
            count++;
            end = intervals[i][1];
        }
    }
    return intervals.size() - count;
}

void print(vector<vector<int>> &nums) {
    for (auto num : nums) {
        for (int i = 0; i < num.size(); i++) {
            cout << num[i] << "  ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int>> nums = {
            {1, 2},
            {2, 3},
            {3, 4},
            {1, 3}
    };
    cout << eraseOverlapIntervals(nums) << endl;
    return 0;
}