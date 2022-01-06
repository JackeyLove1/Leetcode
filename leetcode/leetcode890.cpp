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

class Solution {
public:
    vector<string> findAndReplacePattern(vector<string> &words, string pattern) {
        vector<string> res;
        unordered_map<char, char> um1, um2;
        um1.reserve(25);
        um2.reserve(25);
        pattern = static_cast<const string>(pattern);
        for (const auto &word : words) {
            if (word.size() != pattern.size()) continue;
            um1.clear();
            um2.clear();
            bool flag = true;
            for (int i = 0; i < pattern.size(); ++i) {
                if (!um1.count(pattern[i]) && !um2.count(word[i])) {
                    um1[pattern[i]] = word[i];
                    um2[word[i]] = pattern[i];
                    continue;
                }
                if (um1[pattern[i]] != word[i] || um2[word[i]] != pattern[i]) {
                    flag = false;
                    break;
                }
            }
            if (flag) res.push_back(word);
        }
        return res;
    }
};