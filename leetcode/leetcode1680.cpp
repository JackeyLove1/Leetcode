#include <iostream>
#include "Logger.h"

using namespace std;

#include <unordered_map>
#include <map>
#include <set>

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}


class Solution {
public:
    int concatenatedBinary(int n) {
        constexpr int mod = 1e9 + 7;
        long long res = 0, help = 1;
        for (int i = n; i >= 1; --i) {
            int cur = i;
            while (cur) {
                if (cur & 1) {
                    res = (res + help) % mod;
                };
                // cout << "help: " << help << endl;
                // cout << "res: " << res << endl;
                help %= mod;
                cur >>= 1;
                help <<= 1;
            }
        }
        return static_cast<int>(res);
    }
};

int main() {
    Solution s;
    cout << s.concatenatedBinary(3) << endl;
    cout << s.concatenatedBinary(12) << endl;
}