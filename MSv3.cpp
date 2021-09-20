// Author: Jacky
// Time: 2021-09-19
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
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

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;
const int debug = 0;
using ll = long long;
static int cnt;
static int res;
int _X, _Y;

void dfs(int idx, int cur, ll sum, int depth, vector<int> &A) {
    if (depth > 2 * cnt) return;
    if (sum <= 0) {
        res = min(res, cur);
        if (debug) cout << "cur: " << cur << endl;
        return;
    }
    if (idx == A.size()) return;
    if (debug) cout <<"sum: "<<sum <<" cur: " << cur << endl;
    dfs(idx + 1, cur + _X, sum - A[idx], depth + 1, A);
    dfs(idx + 1, cur + _Y, sum - 2 * A[idx], depth + 1, A);
};

int solution(vector<int> &A, int X, int Y) {
    // write your code in C++14 (g++ 6.2.0)
    ll sum = 0;
    _X = X, _Y = Y;
    for (auto &num : A) {
        sum += num;
    }
    sort(A.begin(), A.end(), [](int x, int y) {
        return x > y;
    });
    if(debug) print(A);
    res = A.size() * X;
    if(debug) cout <<" res: " << res << endl;
    ll tmp = 0, tmpSum = sum;
    cnt = 0;
    for (int i = 0; i < A.size(); ++i) {
        tmp += Y;
        tmpSum -= 2 * A[i];
        ++cnt;
        if (tmpSum <= 0) break;
    }
    if(debug) cout <<" tmp: " << tmp << endl;
    res = min(ll(res), tmp);
    dfs(0, 0, sum, 0, A);
    return res;
}

int main() {
    vector<int> nums = {5, 3, 8, 3, 2};
    cout << solution(nums, 2, 5) << " res:7" << endl;
}