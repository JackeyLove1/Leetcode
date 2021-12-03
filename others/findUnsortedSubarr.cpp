#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <deque>
#include <queue>

using namespace std;

int findUnsortedSubarray(vector<int> &nums) {
    vector<int> tmp(nums.begin(), nums.end());
    sort(tmp.begin(), tmp.end());
    int i = 0, j = nums.size() - 1;
    while (i < nums.size() && nums[i] == tmp[i]) i++;
    while (j >= 0 && nums[j] == tmp[j]) j--;
    int res = j - i + 1;
    if (res == -nums.size()) return 0;
    return res;
}

int main() {
    vector<int> v = {1, 2, 3, 4};
    cout << findUnsortedSubarray(v)<<endl;
    vector<int> v1 = {2,6,4,8,10,9,15};
    cout << findUnsortedSubarray(v1)<<endl;
    vector<int> v2 = {4,3,2,1};
    cout << findUnsortedSubarray(v2)<<endl;
    vector<int> v3 = {4,2,3,1};
    cout << findUnsortedSubarray(v3)<<endl;
    vector<int> v4 = {4,2,31};
    cout << findUnsortedSubarray(v4)<<endl;
}