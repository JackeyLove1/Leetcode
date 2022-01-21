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
#include <stack>


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
    vector<int> subSort(const vector<int> &array) {
        vector<int> vec(array.begin(), array.end());
        sort(vec.begin(), vec.end());
        int l = -1, r = -1;
        for (int i = 0; i < array.size(); ++i) {
            if (array[i] != vec[i]) {
                l = i;
                break;
            }
        }
        for (int i = array.size() - 1; i >= 0; --i) {
            if (array[i] != vec[i]) {
                r = i;
                break;
            }
        }
        return {l, r};
    }
};