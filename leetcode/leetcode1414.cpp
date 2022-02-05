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
    int findMinFibonacciNumbers(int k) {
        // 经典动态规划做法
        vector<int> fib;
        fib.reserve(100);
        unordered_map<int, int> um;
        fib.push_back(1);
        fib.push_back(1);
        int cnt = 2;
        um[0] = 0, um[1] = 1, um[2] = 1;
        while (fib.back() <= k) {
            fib.push_back(fib[cnt - 1] + fib[cnt - 2]);
            um[fib[cnt]] = 1;
            ++cnt;
        }
        reverse(fib.begin(), fib.end());
        int res = 0;
        while (k > 0) {
            auto iter = lower_bound(fib.begin(), fib.end(), k, [](const int a, const int b){
                return a > b;
            });
            // cout << *iter << endl;
            ++res;
            k -= *iter;
        }
        return res;
    }
};

int main() {
    Solution s;
    cout << s.findMinFibonacciNumbers(7) << " res: 2" << endl;
}