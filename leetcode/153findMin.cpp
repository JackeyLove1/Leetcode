#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int findMin(vector<int> &nums) {
    if (nums.empty()) return -1;
    int i = 0, j = nums.size() - 1;
    while (i < j) {
        int mid = i + (j - i) / 2;
        if(nums[mid] <= nums[j])
            j = mid;
        else
            i = mid + 1;
    }
    return nums[i];
}