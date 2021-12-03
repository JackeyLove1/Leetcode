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

template<typename T>
inline void print(vector<T> &nums) {
    for (auto &num : nums) cout << num << " ";
    cout << endl;
}

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for (auto &n : num) {
            cout << n << " ";
        }
        cout << endl;
    }
    cout << "ending .... " << endl;
}

double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
    vector<int> nums3;
    int l = 0, r = 0;
    while (l < nums1.size() && r < nums2.size()) {
        if (nums1[l] <= nums2[r]) {
            nums3.push_back(nums1[l++]);
        } else {
            nums3.push_back(nums2[r++]);
        }
    }
    while (l < nums1.size()) nums3.push_back(nums1[l++]);
    while (r < nums2.size()) nums3.push_back(nums2[r++]);
    // print(nums3);
    if (!(nums3.size() & 1)) {
        return (double(nums3[nums3.size() / 2]) + double(nums3[nums3.size() / 2 - 1])) / 2;
    }
    return double(nums3[nums3.size() / 2]);
}

int main() {
    vector<int> v1 = {1, 2};
    vector<int> v2 = {3};
    cout << findMedianSortedArrays(v1, v2) << " res:2.000" << endl;
}