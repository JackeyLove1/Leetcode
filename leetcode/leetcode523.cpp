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

constexpr int N = 5010;

class Solution {
public:
    bool checkSubarraySum(vector<int> &nums, int k) {
        if (nums.size() < 2) return false;
        vector<int> prefix(nums.size() + 1, 0);
        unordered_map<int, int> um;
        prefix[0] = nums[0];
        um[prefix[0] % k] = 0;
        for (int i = 1; i < nums.size(); ++i) {
            prefix[i] = nums[i] + prefix[i - 1];
            int mod = prefix[i] % k;
            if (mod == 0) return true;
            if (um.count(mod) && i - um[mod] >= 2) return true;
            if (!um.count(mod)) um[mod] = i;
            // cout <<"i: " << i <<" prefix: " << prefix[i] << endl;
            // cout << "mod: " << mod << endl;
        }
        /*
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j <= i - 2; ++j) {
                if ((prefix[i] - prefix[j]) % k == 0)
                    return true;
            }
        }
         */
        return false;
    }
};

int main() {
    Solution s;
    vector<int> v1 = {5, 0, 0, 0};
    cout << s.checkSubarraySum(v1, 3) << endl;
}