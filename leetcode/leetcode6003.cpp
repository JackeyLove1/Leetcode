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
    int minimumTime(string s) {
        int sz = s.size();
        int l = sz / 2;
        int r = l + 1;
        vector<int> f(sz + 10, 0);
        for (int i = r + 1; i < sz; ++i) {
            if (s[i - 1] == '1' && s[i] == '1') f[i] = f[i - 1] + 1;
            if (s[i - 1] == '1' && s[i] == '0') f[i] = f[i - 1] + 2;
            if (s[i - 1] == '0' && s[i] == '1') f[i] = f[i - 1] + 1;
            if (s[i - 1] == '0' && s[i] == '0') f[i] = f[i - 1] + 0;
        }
        for (int i = l - 1; i >= 0; --i) {
            if (s[i + 1] == '1' && s[i] == '1') f[i] = f[i + 1] + 1;
            if (s[i + 1] == '1' && s[i] == '0') f[i] = f[i + 1] + 2;
            if (s[i + 1] == '0' && s[i] == '1') f[i] = f[i + 1] + 1;
            if (s[i + 1] == '0' && s[i] == '0') f[i] = f[i + 1] + 0;
        }
        cout <<"l: " << s[l] <<" r: " << s[r] << endl;
        int res = f[0] + f[sz - 1];
        return res;
    }
};

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
    int minimumTime(const string &s) {
        int sz = s.size();
        int res = 0, l = 0, r = s.size() - 1;
        int one = 0;
        for (const auto ch : s) {
            if (ch == '1') ++one;
        }
        while (l < r && one > 0) {
            while (s[l] == '1' && l < r) {
                ++res;
                ++l;
                if (--one == 0) break;
            }
            while (s[r] == '1' && l < r) {
                ++res;
                --r;
                if (--one == 0) break;
            }
            if (s[l] == '0') {
                ++res;
                while (l < r && s[l] == '0') ++l;
            }
            if (s[r] == '0') {
                ++res;
                while (l < r && s[r] == '0') --r;
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    cout << s.minimumTime("1100101") << " res: 5" << endl;
    cout << s.minimumTime("1001010101") << " res: 8" << endl;
    cout << s.minimumTime("0010") << " res: 2" << endl;
    cout << s.minimumTime("011001111111101001010000001010011") << " res: 25" << endl;
    cout << s.minimumTime("010011") << " res: 4" << endl;
    cout << s.minimumTime("010110") << " res: 5" << endl;
}
