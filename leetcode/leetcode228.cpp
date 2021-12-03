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

vector<string> summaryRanges(vector<int> &nums) {
    vector<string> res;
    if (nums.empty()) return res;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); i++) {
        string tmp = to_string(nums[i]);
        int j = i;
        while (j + 1 < nums.size() && nums[j + 1] == nums[j] + 1) {
            j++;
        }
        if (j != i) {
            i = j;
            tmp = tmp + "->" + to_string(nums[j]);
        }
        res.emplace_back(tmp);
    }
    return res;
}

int main() {
    vector<int> nums = {0, 2, 3, 4, 6, 8, 9};
    auto res = summaryRanges(nums);
    print(res);
    vector<int> nums2 = {-1};
    auto res2 = summaryRanges(nums2);
    print(res2);
    return 0;
}