#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <unordered_map>

using namespace std;

constexpr int INF = 1e9;
using PII = pair<int, int>;
map<PII, int> cache;
unordered_map<int, int> pre;

int dfs(vector<int> &nums, int power, int cur) {
    int n = nums.size();
    PII p = {power, cur};
    if (cache.count(p)) return cache[p];
    cache[p] = -INF;
    int &v = cache[p];
    if (cur == n - 1) return v = max(v, power + nums[cur]);
    for (int i = cur + 1; i < n; ++i) {
        int left = power - int(pow(i - cur, 2)) + nums[cur];
        if (left < 0) continue;
        int next = dfs(nums, left, i);
        v = max(next, v);
        if (v == next) {
            pre[i] = cur;
        }
        // cout << "cur: " << cur << " power: " << power;
        // cout << " i: " << i << " left: " << left << " res: " << v << endl;
    }
    return v;
}

int main() {
    vector<int> nums = {1, 2, -3, 4, 5, 6};
    int m = 5, cur = 0;
    int res = dfs(nums, m, cur);
    if (res == -INF) {
        cout << "impossible" << endl;
        return 0;
    }
    cout << res << endl;
    int curr = nums.size() - 1;
    cout << curr << " ";
    while (pre.count(curr)) {
        cout << pre[curr] << " ";
        curr = pre[curr];
    }
    return 0;
}