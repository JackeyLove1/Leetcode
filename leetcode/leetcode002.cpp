#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <atomic>
#include <thread>

#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

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

inline int count(int state) {
    return __builtin_popcount(state);
}

class Solution {
public:
    string addBinary(string a, string b) {
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        string c;
        int sz = max(a.size(), b.size());
        int x = 0, y = 0, sum = 0, carry = 0;
        for (int i = 0; i < sz; ++i) {
            x = i < a.size() ? (a[i] - '0') : 0;
            y = i < b.size() ? (b[i] - '0') : 0;
            sum = x + y + carry;
            c.push_back(sum % 2 + '0');
            carry = sum / 2;
        }
        if (carry) c.push_back('1');
        reverse(c.begin(), c.end());
        return c;
    }
};