#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <unordered_map>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>

using namespace std;

constexpr int N = 1e3 + 100;
using PII = pair<int, int>; // numbers 0, numbers 1
PII q[N];
int f[N];

int solve(int nums[], int n) {
    for (int i = 1; i <= n; ++i) {
        q[i] = q[i - 1];
        if (nums[i]) {
            ++q[i].second;
        } else {
            ++q[i].first;
        }
    }
    int maxn = 0, idx = -1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < i; ++j) {
            if (q[i].second - q[j - 1].second > q[i].first - q[j - 1].first) {
                // [j, i] 区间j到i的1个数是否大于0个数
                f[i] = max(f[j - 1] + 1, f[i]);
                maxn = max(maxn, f[i]);
                if (maxn == f[i]) idx = i;
            }
        }
    }
    // 区间结尾idx区间长度maxn可以反推出区间
    return maxn;
}
