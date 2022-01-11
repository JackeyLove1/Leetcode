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

class TreeNode {
public:
    int val;
    TreeNode *left, *right;

    explicit TreeNode(int val_) : val(val_), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int longestPalindrome(vector<string> &words) {
        unordered_map<string, int> um;
        bool flag = false;
        for (const auto &word : words) {
            um[word]++;
        }
        int cnt = 0;
        bool mid = false;
        for (auto&[word, num] : um) {
            if (word[0] == word[1]) {
                if (num % 2 == 1) {
                    if (!mid) {
                        cnt += 2;
                        mid = true;
                    }
                    cnt += (num - 1) * 2;
                } else {
                    cnt += num * 2;
                }
            } else {
                string other = word;
                swap(other[0], other[1]);
                if (um[other] > 0) {
                    int sz = min(num, um[other]);
                    cnt += sz * 4;
                    um[word] -= sz;
                    um[other] -= sz;
                }
            }

        }
        return cnt;
    }
};

int main() {
    Solution s;
    vector<string> v1 = {"oo", "vv", "uu", "gg", "pp", "ff", "ss", "yy", "vv", "cc",
                         "rr", "ig", "jj", "uu", "ig", "gb", "zz", "xx", "ff", "bb",
                         "ii", "dd", "ii", "ee", "mm", "qq", "ig", "ww", "ss", "tt",
                         "vv", "oo", "ww", "ss", "bi", "ff", "gg", "bi", "jj", "ee",
                         "gb", "qq", "bg", "nn", "vv", "oo", "bb", "pp", "ww", "qq",
                         "mm", "ee", "tt", "hh", "ss", "tt", "ee", "gi", "ig", "uu",
                         "ff", "zz", "ii", "ff", "ss", "gi", "yy", "gb", "mm", "pp",
                         "uu", "kk", "jj", "ee"};

    cout << s.longestPalindrome(v1) << " res: 102" << endl;
}