#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <functional>
#include <queue>
#include <set>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for (auto &num : nums) cout << num << " ";
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
    cout << "ending .... " << endl;
}

// 记忆化搜索
int solve(vector<int> &m, vector<int> &nums, int idx) {
    int &v = m[idx];
    if (v != -1) return v;
    for (int i = 1; i <= nums[idx] && (idx + i) < nums.size(); i++) {
        v = max(max(v, idx + i), solve(m, nums, idx + i));
    }
    // cout << "idx: " << idx << " v: " << v << endl;
    return v;
}

bool canJump(vector<int> &nums) {
    int n = nums.size();
    if (n == 1) return true;
    vector<int> m(n + 1, -1);
    m[n - 1] = n - 1;
    if (solve(m, nums, 0) >= n - 1)
        return true;
    return false;
}

int main() {
    vector<int> v1 = {2, 3, 1, 1, 4};
    cout << canJump(v1) << " res: true" << endl;
    vector<int> v2 = {3, 2, 1, 0, 4};
    cout << canJump(v2) << " res: false" << endl;
    vector<int> v3 = {0, 2, 3};
    cout << canJump(v3) << " res: false" << endl;
}