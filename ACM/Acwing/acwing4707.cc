#pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}


inline int read() {
    int ans = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c)) {
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return ans;
}

int nums[1200];

int main() {
    int n = read();
    // memset(nums, 0, sizeof nums);
    int res = 1e9;
    for (int i = 1; i <= n; ++i) {
        nums[i] = read();
        if (i != 1) res = std::min(res, std::abs(nums[i] - nums[i - 1]));
    }
    res = std::min(res, std::abs(nums[n] - nums[1]));
    cout << res << endl;
    return 0;
}