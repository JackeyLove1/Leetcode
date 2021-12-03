#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

// 使用二分查找找到目标元素再往周围扩展的方法
// 升序数列
int findTarget(vector<int> &nums, int target) {
    int i = 0, j = nums.size() - 1;
    while (i <= j) {
        int mid = i + (j - i) / 2;
        if (nums[mid] == target)
            return mid;
        else if (nums[mid] > target)
            j = mid - 1;
        else
            i = mid + 1;
    }
    return -1;
}

vector<int> searchRange(vector<int> &nums, int target) {
    vector<int> res = {-1, -1};
    int mid = findTarget(nums, target);
    if (mid == -1) return res;
    // cout << mid << "     ";
    int l = mid, r = mid;
    while (l - 1 >= 0 && nums[l - 1] == target) l--;
    while (r + 1 < nums.size() && nums[r + 1] == target) r++;
    res[0] = l;
    res[1] = r;
    return res;
}

void print(vector<int> nums) {
    for (auto num : nums)
        cout << num << "  ";
    cout << endl;
}

int main() {
    vector<int> nums = {5, 7, 7, 8, 8, 10};
    vector<int> res1 = searchRange(nums, 8);
    vector<int> res2 = searchRange(nums, 6);
    vector<int> nums1 = {1};
    vector<int> res3 = searchRange(nums1, 1);
    print(res1);
    print(res2);
    print(res3);
    return 0;
}