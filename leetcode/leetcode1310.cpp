#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

#pragma GCC optimize(2)

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
    vector<int> xorQueries(const vector<int> &arr, const vector<vector<int>> &queries) {
        int sz = arr.size();
        vector<int> prefix(sz + 5, 0);
        for (int i = 1; i <= sz; ++i) {
            prefix[i] = arr[i - 1] ^ prefix[i - 1];
        }
        vector<int> res(queries.size(), 0);
        for (int i = 0; i < queries.size(); ++i) {
            int l = queries[i][0], r = queries[i][1];
            res[i] = prefix[r + 1] ^ prefix[l + 1];
        }
        return res;
    }
};