// Author: Jacky
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>
#include <numeric>


using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

class Solution {
public:
    int countMaxOrSubsets(vector<int> &nums) {
        unordered_map<int, int> m;
        int n = nums.size(), maxn = 0;
        for (int i = 0; i < (1 << n); ++i) {
            int sum = 0;
            for (int j = 0; j < n; ++j) {
                if (i & (1 << j)) {
                    sum |= nums[j];
                }
            }
            ++m[sum];
            maxn = max(maxn, sum);
        }
        return m[maxn];
    }
};