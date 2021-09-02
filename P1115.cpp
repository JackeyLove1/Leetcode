#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <climits>
#include <functional>

using namespace std;

int n;
constexpr int N = 1e6;
int nums[N], f[N], s[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
        s[i] = s[i - 1] + nums[i];
    }
    priority_queue<int, vector<int>, greater<int>> minq;// 最小堆
    minq.push(0);
    int res = INT_MIN;
    for (int i = 1; i <= n; i++) {
        res = max(res, s[i] - minq.top());
        minq.push(s[i]);
    }
    cout << res << endl;
    return 0;
}