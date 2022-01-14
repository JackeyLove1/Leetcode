#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <utility>
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
    bool canArrange(vector<int>& arr, int k) {
        unordered_map<int, int> mod;
        for (int num: arr) {
            ++mod[(num % k + k) % k];
        }
        for (auto [t, occ]: mod) {
            if (t > 0 && (!mod.count(k - t) || mod[k - t] != occ)) {
                return false;
            }
        }
        return mod[0] % 2 == 0;
    }
};

