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

constexpr int N = 1e6 + 10;

class Solution {
public:
    bool buddyStrings(string s, string goal) {
        s = static_cast<const string>(s);
        goal = static_cast<const string>(goal);
        if (s.size() != goal.size()) return false;
        vector<int> idx;
        idx.reserve(10);
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] != goal[i]) {
                idx.push_back(i);
                if (idx.size() > 2) return false;
            }
        }

        if (idx.empty()) {
            vector<int> vec(26);
            for (const char ch : s) {
                if (++vec[ch - 'a'] >= 2) return true;
            }
            return false;
        }
        if (idx.size() == 1) return false;
        return s[idx[0]] == goal[idx[1]] && s[idx[1]] == goal[idx[0]];
    }
};