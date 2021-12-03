//
// Created by Jacky on 2021/9/5.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <unordered_map>

using namespace std;

int n;
constexpr int N = 1e6;
int nums[N];

inline void print(int l, int r) {
    for (int i = l; i <= r; i++) {
        cout << nums[i] << ' ';
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> nums[i];
    int res = 0;
    for (int i = 1; i < n; i++) {
        int minn = nums[i + 1];
        for (int j = i + 1; j <= n; j++) {
            if (j == i + 1 || (minn >= nums[j] && minn >= nums[i])) {
                ++res;
                minn = min(minn, nums[j]);
                // print(i, j);
            }
        }
    }
    cout << res << endl;
    return 0;
}