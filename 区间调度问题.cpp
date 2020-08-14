#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

// 区间调度问题
bool cmp(vector<int> &a, vector<int> &b) {
    return a[1] < b[1];
}

int eraseOverlapIntervals(vector<vector<int>> &intervals) {
    int n = intervals.size();
//    cout<<"n = "<<n<<endl;
    if (n == 0) return 0;
    if (n == 1) return 1;
    sort(intervals.begin(), intervals.end(), cmp);
    for (auto ints : intervals) {
        cout << "ints is " << ints[0] << "  " << ints[1] << endl;
    }
    int cnt = 1;
    int x_end = intervals[0][1];
    for (int i = 1; i < n; i++) {
        if (intervals[i][0] >= x_end) {
            x_end = intervals[i][1];
            cnt++;
        }
    }
    return cnt;
}

// test function
int main() {
    vector<vector<int> > intervals = {{1, 2},
                                      {2, 3},
                                      {3, 4},
                                      {1, 3}};
    cout << eraseOverlapIntervals(intervals) << endl;
    return 0;
}