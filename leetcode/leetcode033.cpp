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
    vector<vector<string>> groupAnagrams(vector<string> &strs) {
        if (strs.empty()) return {};
        unordered_map<string, vector<string>> m;
        for (auto &str : strs) {
            string tmp = str;
            sort(tmp.begin(), tmp.end());
            m[tmp].emplace_back(str);
        }
        vector<vector<string>> res;
        res.reserve(m.size());
        for (auto&[_, v] : m) {
            res.emplace_back(v);
        }
        return res;
    }
};
