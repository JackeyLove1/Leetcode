#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstring>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

constexpr int N = 1e6 + 100;

int q[N];

int findUnsortedSubarray(vector<int> &nums) {
    int n = nums.size();
    vector<int> numsCopy(nums.begin(), nums.end());
    sort(numsCopy.begin(), numsCopy.end());
    int l = 0, r = n - 1;
    while (l < n && nums[l] == numsCopy[l]) l++;
    while (r >= 0 && nums[r] == numsCopy[r]) r--;
    return r - l + 1 < 0 ? 0 : r - l + 1;
}

int main() {
    vector<int> nums1 = {2, 6, 4, 8, 10, 9, 15};
    cout << findUnsortedSubarray(nums1) << " res: 5" << endl;
    vector<int> nums2 = {1, 2, 3, 4};
    cout << findUnsortedSubarray(nums2) << " res: 0" << endl;
    vector<int> nums3 = {1};
    cout << findUnsortedSubarray(nums3) << " res: 0" << endl;
}