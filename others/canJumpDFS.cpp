#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

// dfs
bool dfs(vector<int> &nums, int cur) {
    if (cur >= nums.size()) return false;
    if (cur == nums.size() - 1) return true;
    if (nums[cur] == 0) return false;
    for (int i = 1; i <= nums[cur]; i++) {
        if (dfs(nums, cur + i))
            return true;
    }
    return false;
}

bool canJump(vector<int> &nums) {
    return dfs(nums, 0);
}

int main() {
    vector<int> nums = {2, 3, 1, 1, 4};
    cout << canJump(nums) << endl;
    vector<int> nums1 = {3,2,1,0,4};
    cout << canJump(nums1) << endl;
    return 0;
}