#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <numeric>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    long long minimumDifference(vector<int> &nums) {
        using ll = long long;
        priority_queue<ll, vector<ll>, greater<>> h1; // 小根堆
        priority_queue<ll, vector<ll>, less<>> h2; // 大根堆
        const int sz = nums.size();
        int n = sz / 3;
        vector<ll> left(sz +5 , 0);
        vector<ll> right(sz +5, 0);
        for (int i = 0; i < n; ++i) {
            left[n - 1] += nums[i];
            h2.push(nums[i]);
        }
        for (int i = n; i < sz; ++i) {
            left[i] = left[i - 1];
            if (h2.top() > nums[i]) {
                left[i] -= h2.top();
                left[i] += nums[i];
                h2.pop();
                h2.push(nums[i]);
            }
        }
        reverse(nums.begin(), nums.end());
        for (int i = 0; i < n; ++i) {
            right[n - 1] += nums[i];
            h1.push(nums[i]);
        }
        for (int i = n; i < sz; ++i) {
            right[i] = right[i - 1];
            if (h1.top() < nums[i]) {
                right[i] -= h1.top();
                right[i] += nums[i];
                h1.pop();
                h1.push(nums[i]);
            }
        }
        // print(left);
        // print(right);
        ll res = INT64_MAX;
        for (int i = n - 1; i < sz - n; ++i) {
            res = min(res, left[i] - right[sz - n - i]);
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> v1 = {3, 1, 2};
    // cout << s.minimumDifference(v1) << " res: -1" << endl;
    vector<int> v2 = {7, 9, 5, 8, 1, 3};
    // cout << s.minimumDifference(v2) << " res: 1" << endl;
    vector<int> v3 = {16,46,43,41,42,14,36,49,50,28,38,25,17,5,18,11,14,21,23,39,23};
    cout << s.minimumDifference(v3) <<" res: -14" << endl;
}