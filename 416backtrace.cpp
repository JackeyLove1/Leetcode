#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <stack>

using namespace std;

// 使用回溯法解决
bool dfs(vector<int> &nums, int target, int start) {
    if(target == 0) return true;
    if (start >= nums.size()) return false;
    if (target < nums[start]) return false;
    for (int i = start; i < nums.size(); i++) {
        return dfs(nums, target-nums[i], start+1) || dfs(nums, target, start+1);
    }
    return false;
}

bool canPartition(vector<int> &nums) {
    int sum = 0;
    for (int i = 0; i < nums.size(); i++) {
        sum += nums[i];
    }
    if (sum % 2 != 0) return false;
    int target = sum / 2;
    if(*max_element(nums.begin(), nums.end()) > target) return false;
    sort(nums.begin(), nums.end());
    return dfs(nums, target, 0);
}

int main(){
    vector<int> vec = {1,5,11,5};
    cout<<canPartition(vec)<<endl;
    vector<int> vec2 = {1,2,3,5};
    cout<<canPartition(vec2)<<endl;
}