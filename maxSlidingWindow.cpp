#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <deque>
#include <queue>

using namespace std;

vector<int> maxSlidingWindow(vector<int> &nums, int k) {
    int maxPlace = -1, left = 0, right = k - 1;
    vector<int> res;
    while (right < nums.size()) {
        if (maxPlace < left) {
            int temp = nums[left], maxPlace = left;
            for (int i = left; i <= right; i++) {
                temp = max(temp, nums[i]);
                if (temp == nums[i]) maxPlace = i;
            }
            res.push_back(temp);
            left++;
            right++;
        } else {
            res.push_back(nums[maxPlace]);
            left++;
            right++;
        }
    }
    return res;
}

void print(vector<int> &nums) {
    for (auto num : nums)
        cout << num << "  ";
    cout << endl;
}

int main() {
    vector<int> nums = {1,3,-1,-3,5,3,6,7};
    int k = 3;
    vector<int> v = maxSlidingWindow(nums, k);
    print(v);
}