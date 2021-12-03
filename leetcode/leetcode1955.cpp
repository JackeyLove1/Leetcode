#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <bitset>
#include <cstring>
#include <string>

using namespace std;

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for_each(num.begin(), num.end(), [](const T &t) { cout << t << " "; });
        cout << endl;
    }
}

template<typename T>
inline void print(vector<T> &num) {
    for_each(num.begin(), num.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    int countSpecialSubsequences(vector<int> &nums) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        int f0 = 0, f1 = 0, f2 = 0;
        for (auto &num : nums) {
            if (num == 0) {
                f0 = (f0 * 2 + 1) % MOD;
            } else if (num == 1) {
                f1 = ((f1 * 2) % MOD + f0) % MOD;
            } else {
                f2 = ((f2 * 2) % MOD + f1) % MOD;
            }
        }
        return f2;
    }
};