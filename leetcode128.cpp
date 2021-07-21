#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <queue>
#include <set>

using namespace std;

int longestConsecutive(vector<int> &nums) {
    if (nums.empty()) return 0;
    unordered_map<int, int> um;
    unordered_set<int> visited;
    for (auto &num : nums) {
        um[num]++;
    }
    int res = 0;
    // sort(nums.begin(), nums.end());
    for (auto num : nums) {
        if (visited.count(num)) continue;
        visited.insert(num);
        int tmp = 1;
        while (um.find(num + 1) != um.end()) {
            num++, tmp++;
            visited.insert(num);
        }
        res = max(res, tmp);
    }
    return res;
}

int main() {
    vector<int> nums = {100, 4, 200, 1, 3, 2};
    cout << longestConsecutive(nums) << " res:4" << endl;
    vector<int> nums2 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    cout << longestConsecutive(nums2) << " res:9" << endl;
    vector<int> nums3 = {9, 1, 4, 7, 3, -1, 0, 5, 8, -1, 6};
    cout << longestConsecutive(nums3) << " res:7" << endl;
    return 0;

}