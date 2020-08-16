#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <deque>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};


int minDays(int n) {
    vector<long> dp(n + 1, 0);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (i % 2 != 0 && i % 3!=0) {
            dp[i] = dp[i - 1] + 1;
        } else if (i % 2 == 0 && i % 3 != 0) {
            dp[i] = min(dp[i / 2] + 1, dp[i - 1] + 1);
        } else {
            dp[i] = dp[i / 3] + 1;
        }
    }
    return dp[n];
}

int main() {
    cout << minDays(10) << endl;
    cout << minDays(6) << endl;
    cout << minDays(1) << endl;
    cout << minDays(56) << endl;
}