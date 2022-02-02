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

class Solution1 {
public:
    int minOperations(const vector<int> &nums, int x) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum < x) return -1;
        vector<int> left(nums.size(), 0), right(nums.size(), 0);
        int cnt = INT_MAX;
        const int sz = nums.size();
        left[0] = nums.front(), right[nums.size() - 1] = nums.back();
        if (x == 0) return 0;
        if (x == left[0] || x == right.back()) return 1;
        for (int i = 1; i < nums.size(); ++i) {
            left[i] = left[i - 1] + nums[i]; // 左缀和
            if (left[i] == x) cnt = min(cnt, i + 1);
        }
        for (int i = nums.size() - 2; i >= 0; --i) {
            right[i] = right[i + 1] + nums[i];// 右缀和
            if (right[i] == x) cnt = min(cnt, sz - i);
        }
        // cout << "sz: " << sz << endl;
        for (int i = 0; i < sz; ++i) {
            for (int j = sz - 1; j > i; --j) {
                if (left[i] + right[j] == x) {
                    // cout << "i: " << i << " j: " << j << endl;
                    cnt = min(cnt, i + 1 + sz - j);
                }
            }
        }
        return cnt == INT_MAX ? -1 : cnt;
    }
};

// 使用前缀和+哈希可以更好的解决这个问题
class Solution {
public:
    int minOperations(const vector<int> &nums, int x) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum < x) return -1;
        vector<int> psum(nums.size(), 0);
        unordered_map<int, int> mp; // 更新，永远都是最小index
        int cnt = INT_MAX;
        const int sz = nums.size();
        psum[0] = nums[0];
        mp[psum[0]] = 0;
        // mp.find(x-(sum - psum[i])) -> 有解
        for (int i = 1; i < nums.size(); ++i) {
            if (mp.count(x - (sum - psum[i]))) {
                int index = mp[x - (sum - psum[i])];
                cnt = min(cnt, index + 1 + sz - i - 1);
            }
            if (mp.count(psum[i]))continue;
            mp[psum[i]] = i;
        }
        return cnt == INT_MAX ? -1 : cnt;
    }
};

int main() {
    Solution s;
    vector<int> v1 = {3, 2, 20, 1, 1, 3};
    cout << s.minOperations(v1, 10) << " res: 5" << endl;
    vector<int> v2 = {1, 1, 4, 2, 3};
    cout << s.minOperations(v1, 5) << " res: 2" << endl;
}