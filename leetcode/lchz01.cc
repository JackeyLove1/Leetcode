#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>

using namespace std;

vector<vector<int>> solve(vector<int>& nums, int target){
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    unordered_map<int, int> um;
    for(const int num : nums){
        um[num]++;
    }
    set<vector<int>> s;
    for (int i = 0; i < nums.size(); ++i){
        int l = i;
        int r = nums.size() - 1;
        while (l < r){
            auto t = target - nums[l] - nums[r];
            if (t > nums[r]) break;
            if (um.count(t) && t != nums[l] && t != nums[r]){
                auto tmp = vector<int>{nums[l], t, nums[r]};
                sort(tmp.begin(), tmp.end());
                s.emplace(tmp);
            }
            if (t > nums[l]){
                ++l;
            }else {
                --r;
            }
        }
    }
    return vector<vector<int>>(s.begin(), s.end());
}

int main(){
    vector<int>v = {1,4,5,6,7,10,12,15};
    int target = 18;
    auto res = solve(v, target);
    for (auto& nums : res){
        for (auto& num : nums){
            cout << num<<" ";
        }
        cout << endl;
    }
}