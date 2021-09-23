// Author: Jacky
// Time: 2021-09-22
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for (auto &n : num) {
            cout << n << " ";
        }
        cout << endl;
    }
    // cout << "ending ... " << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

int n;
constexpr int N = 1e5 + 100;
int nums[N];
using ll = long long;

int main() {
    fhj();
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> nums[i];
    sort(nums, nums + n);
    int mid1 = nums[n / 2], mid2 = nums[n / 2 + 1];
    ll res1 = 0, res2 = 0;
    for (int i = 0; i < n; ++i) {
        res1 += abs(nums[i] - mid1);
        res2 += abs(nums[i] - mid2);
    }
    cout << min(res1, res2) << endl;
    return 0;
}