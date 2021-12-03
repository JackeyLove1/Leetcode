#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstring>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <cmath>

using namespace std;

constexpr int N = 1e6 + 100;

inline bool judge(const int a, const int b, const int c) {
    return a + b > c && a + c > b && c + b > a;
}

inline int findLeft(int l, int r, int target, vector<int> &nums) {
    if (l > r) return -1;
    while (l < r) {
        int mid = l + r >> 1;
        if (target > nums[mid]) l = mid + 1;
        else r = mid;
    }
    return l;
}

inline int findRight(int l, int r, int target, vector<int> &nums) {
    if (l > r) return -1;
    while (l < r) {
        int mid = l + r + 1 >> 1;
        if (target > nums[mid]) r = mid - 1;
        else l = mid;
    }
    return l;
}

int triangleNumber(vector<int> &nums) {
    int res = 0, n = nums.size();
    sort(nums.begin(), nums.end());
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // cout << "i: " << i << " nums[i]: " << nums[i] << " j: " << j << " nums[j]: " << nums[j] << endl;
            int l = findLeft(j + 1, n - 1, nums[j] - nums[i], nums);
            int r = findRight(j + 1, n - 1, nums[j] + nums[i], nums);
            // cout << "l: " << l << " nums[l]: " << nums[l] << endl;
            // cout << "r: " << r << " nums[r]: " << nums[r] << endl;
            if (l == -1 || r == -1) break;
            for (int k = l; k <= r; k++) {
                if (judge(nums[i], nums[j], nums[k])) {
                    // cout << nums[i] << " " << nums[j] << " " << nums[k] << endl;
                    res++;
                }
            }
        }
    }
    return res;
}

int main() {
    vector<int> nums = {2, 2, 3, 4};
    cout << triangleNumber(nums) << " res:3" << endl;
    return 0;
}