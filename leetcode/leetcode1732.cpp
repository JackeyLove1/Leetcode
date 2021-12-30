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
#include <cstring>
#include <cmath>
#include <list>
#include <atomic>
#include <cstring>
#include <cstdlib>
#include <tuple>
#include <climits>

using namespace std;

template<typename T>
static inline void print(vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    int largestAltitude(vector<int> &gain) {
        int sz = gain.size();
        vector<int> res(sz + 1, 0);
        int max_height = 0;
        for (int i = 0; i < sz; ++i) {
            res[i + 1] = res[i] + gain[i];
            max_height = max(max_height, res[i+1]);
        }
        return max_height;
    }
};