#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;

int ans = INT_MIN;

void dfs(vector<int>&nums, int left, int right, int k, int sum){
    if (k == 0) {, 
        ans = max(sum, ans);
        return;
    }
    dfs(nums, left+1, right, k-1, sum+nums[left]);
    dfs(nums, left, right-1, k-1, sum+nums[right]);
}
int maxScore(vector<int>& cardPoints, int k) {
    dfs(cardPoints, 0, cardPoints.size()-1, k, 0);
    return ans;
}

