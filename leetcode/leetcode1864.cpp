#include <iostream>
#include <utility>
#include <future>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}


class Solution {
public:
    int minSwaps(string s) {
        int one = 0, zero = 0;
        for (auto &ch : s) {
            if (ch == '0') ++zero;
            else ++one;
        }
        // cout << "one: " << one << " zero: " << zero << endl;
        if (!(zero == one || zero == one + 1 || zero + 1 == one)) {
            return -1;
        }
        int n = s.size();
        string sZero, sOne;
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                sZero.push_back('0');
                sOne.push_back('1');
            } else {
                sZero.push_back('1');
                sOne.push_back('0');
            }
        }
        int disZero = 0, disOne = 0;
        for (int i = 0; i < n; ++i) {
            if (sZero[i] != s[i]) ++disZero;
            if (sOne[i] != s[i]) ++disOne;
        }
        if (zero == one) return min(disZero, disOne) / 2;
        if (zero > one) return disZero / 2;
        return disOne / 2;
    }
};

int main() {
    Solution s;
    cout << s.minSwaps("111000") << endl;
    cout << s.minSwaps("100") << endl;
}