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
    vector<string> buildArray(const vector<int>& target, int n) {
        vector<string> res;
        int p1 = 0, p2 = 1;
        while (p1 < target.size() && p2 <= n){
            if(target[p1] != p2){
                res.emplace_back("Push");
                res.emplace_back("Pop");
                ++p2;
                continue;
            }
            if(target[p1] == p2){
                res.emplace_back("Push");
                ++p2;
                ++p1;
                continue;
            }
        }
        return res;
    }
};