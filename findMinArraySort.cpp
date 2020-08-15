#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

static bool cmp(vector<int> &v1, vector<int> &v2) {
    return v1[1] < v2[1];
}

int findMinArrowShots(vector<vector<int>> &points) {
    if (points.empty()) return 0;
    sort(points.begin(), points.end(), cmp);
    int start = points[0][0], end = points[0][1];
    int count = 1;
    for (int i = 1; i < points.size(); i++) {
        if(points[i][0] > end){
            count++;
            end = points[i][1];
        }
    }
    return count;
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
    return 0;
}