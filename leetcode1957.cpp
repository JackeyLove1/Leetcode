#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <bitset>
#include <cstring>
#include <string>

using namespace std;

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for_each(num.begin(), num.end(), [](const T &t) { cout << t << " "; });
        cout << endl;
    }
}

template<typename T>
inline void print(vector<T> &num) {
    for_each(num.begin(), num.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    string makeFancyString(string s) {
        if (s.size() < 3) return s;
        int cnt = 1;
        string res;
        res.push_back(s[0]);
        for (int i = 1; i < s.size(); i++) {
            if (s[i] != s[i - 1]) {
                cnt = 1;
                res.push_back(s[i]);
            } else {
                if (++cnt == 3) {
                    --cnt;
                    continue;
                } else {
                    res.push_back(s[i]);
                }
            }
        }
        return res;
    }
};

int main() {
    auto s = Solution();
    cout << s.makeFancyString("aaabaaaa") << " res: aabaa" << endl;
    return 0;
}