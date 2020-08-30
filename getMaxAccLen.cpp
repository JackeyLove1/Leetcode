#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <deque>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

int getMaxLen(vector<int> &nums) {
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    vector<vector<int>> len(n, vector<int>(n, 0));
    dp[0][0] = nums[0];
    dp[0][1] = nums[0];
    len[0][0] = 1;
    len[0][1] = 1;
    for (int i = 1; i < n; i++) {
        dp[i][0] = nums[i];
        len[i][0] = 1;
        dp[i][1] = max(dp[i - 1][0] * nums[i], dp[i - 1][1] * nums[i]);
        if (dp[i][1] == dp[i - 1][1] * nums[i])
            len[i][1] = len[i - 1][1] + 1;
        else
            len[i][1] = len[i - 1][0] + 1;
        cout<<"dp[i][0] = "<<dp[i][0]<<"  dp[i][1] = "<<dp[i][1]<<endl;
    }
    int maxNumber = INT_MIN;
    int res = 0;
    for (int i = 0; i < n; i++) {
        if(dp[i][0] > maxNumber && dp[i][0] > 0){
            maxNumber = dp[i][0];
            res = len[i][0];
        }
        if(dp[i][1] > maxNumber && dp[i][1] > 0){
            maxNumber = dp[i][1];
            res = len[i][1];
        }
    }
    return res;
}

int main(){
    vector<int> nums = {0,1,-2,-3,-4};
    cout<<getMaxLen(nums)<<endl;
}