#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
// #pragma GCC optimize(2)

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

class Solution {
private:
    static inline char transform(char ch) {
        if (ch >= 'a' && ch <= 'z')
            ch -= 32;
        else if (ch >= 'A' && ch <= 'Z')
            ch += 32;
        return ch;
    }

public:
    string longestNiceSubstring(const string &s) {
        unordered_map<char, int> mp;
        string res;
        auto check = [&]() -> bool {
            for (const auto&[k, v] : mp) {
                if (v > 0) {
                    auto ch = transform(k);
                    if (mp[ch] <= 0) return false;
                }
            }
            return true;
        };
        for (int l = 0, r = 0; r < s.size(); ++r) {
            ++mp[s[r]];
            if (check() && res.size() < r - l + 1) res = s.substr(l, r - l + 1);
            while (l < r && !check()) {
                --mp[s[l--]];
            }
        }
        return res;
    }
};