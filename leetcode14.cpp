#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <functional>

using namespace std;

inline void print(vector<int> &nums) {
    for (auto &num : nums) cout << num << " ";
    // cout << "end..." << endl;
}

vector<vector<int>> fourSum(vector<int> &nums, int target) {
    vector<vector<int>> res;
    int n = nums.size();
    sort(nums.begin(), nums.end());
    if (n < 4) return res;
    for (int a = 0; a <= n - 4; a++) {
        if (a > 0 && nums[a] == nums[a - 1]) continue;
        // cout << "a: " << a << endl;
        for (int b = a + 1; b <= n - 3; b++) {
            // cout << "b: " << b << endl;
            if (b > a + 1 && nums[b] == nums[b - 1]) continue;
            int c = b + 1, d = n - 1;
            int t = target - nums[a] - nums[b];
            // if (t < 0) break;
            while (c < d) {
                int partSum = nums[c] + nums[d];
                if (partSum > t) {
                    d--;
                } else if (partSum == t) {
                    res.push_back({nums[a], nums[b], nums[c], nums[d]});
                    while (c < d && nums[c + 1] == nums[c])
                        c++;
                    while (c < d && nums[d - 1] == nums[d])
                        d--;
                    c++;
                    d--;
                } else {
                    c++;
                }
            }
        }
    }
    return res;
}

int main() {
    vector<int> nums = {1, -2, -5, -4, -3, 3, 3, 5};
    auto res = fourSum(nums, -11);
    for_each(res.begin(), res.end(), print);
}