#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <deque>

using namespace std;

vector<int> runningSum(vector<int>& nums) {
    for(int i = 1;i<nums.size();i++){
        nums[i] = nums[i-1]+nums[i];
    }
    return nums;
}