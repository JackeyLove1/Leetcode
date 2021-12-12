#include <unordered_map>
#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    int minFlips(int a, int b, int c) {
        int res = 0;
        while (a || b || c) {
            // cout << "a&1: " << (a & 1) << endl;
            // cout << "b&1: " << (b & 1) << endl;
            // cout << "c&1: " << (c & 1) << endl;
            if (c & 1) {
                if (!(a & 1) && !(b & 1)) res += 1;
            } else {
                res += (a & 1) + (b & 1);
            }
            c >>= 1;
            b >>= 1;
            a >>= 1;

            // cout << res << endl;
        }
        return res;
    }
};

int main() {
    Solution s;
    cout << s.minFlips(2, 6, 5) << " res: 3" << endl;
    cout << s.minFlips(8, 3, 5) << " res: 3" << endl;
}