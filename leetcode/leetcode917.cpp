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
#include <numeric>

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
public:
    string reverseOnlyLetters(string s) {
        int l = 0, r = s.size() - 1;
        while (l < r) {
            while (l < r && !isalpha(s[l])) ++l;
            cout << "l: " << l << endl;
            while (l < r && !isalpha(s[r])) --r;
            cout << "r: " << r << endl;
            if (l < r) swap(s[l], s[r]);
            ++l, --r;
        }
        return s;
    }
};

int main() {
    Solution s;
    cout << s.reverseOnlyLetters("ab-cd") << endl;
}