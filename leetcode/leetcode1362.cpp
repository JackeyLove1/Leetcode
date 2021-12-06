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
    vector<int> closestDivisors(int num) {
        int sq = int(sqrt(num)) + 1;
        using ll = long long int;
        ll t1 = num + 1, t2 = num + 2;
        ll min_gap = 1e9;
        vector<int> res(2, 0);
        for (ll i = sq; i; --i) {
            if (t1 % i == 0) {
                ll l1 = t1 / i;
                if (min_gap > abs(l1 - i)) {
                    min_gap = abs(l1 - i);
                    res = {static_cast<int>(i), static_cast<int>(l1)};
                }
            }
            if (t2 % i == 0) {
                ll l2 = t2 / i;
                if (min_gap > abs(l2 - i)) {
                    min_gap = abs(l2 - i);
                    res = {static_cast<int>(i), static_cast<int>(l2)};
                }
            }
        }
        return res;
    }
};

int main() {
    // cout << int(sqrt(8)) << endl;
    Solution s;
    auto vec1 = s.closestDivisors(8);
    print(vec1);
    auto vec2 = s.closestDivisors(1);
    print(vec2);
    auto v3 = s.closestDivisors(170967091);
    print(v3);
}