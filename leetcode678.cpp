// Author: Jacky
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>
#include <numeric>


using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

inline int count(int x) {
    return __builtin_popcount(x);
}

constexpr int N = 1e6, M = 1e3 + 100, INF = 0x3f3f3f3f;

class Solution {
public:
    bool checkValidString(string s) {
        if (s.empty()) return true;
        vector<vector<int>> f(101, vector<int>(101, -1));
        function<bool(int, int)> check = [&](int i, int j) -> bool {
            if (i > j) return false;
            int &v = f[i][j] = 0;
            if (i == j && s[i] == '*') return v = true;
            if (i == j && s[i] != '*') return v = false;
            if ((i + 1 == j) && (s[i] == '(' || s[i] == '*') && (s[j] == ')' || s[j] == '*')) {
                return true;
            }
            if ((s[i] == '(' || s[i] == '*') && (s[j] == ')' || s[j] == '*')) {
                v = v || check(i + 1, j - 1);
            }
            if (s[i] == '*') {
                v = v || check(i + 1, j);
            }
            if (s[j] == '*') {
                v = v || check(i, j - 1);
            }
            return v;
        };
        return check(0, s.size() - 1);
    }
};

class Solution1 {
public:
    bool checkValidString(string s) {
        if (s.empty()) return true;
        vector<vector<int>> f(101, vector<int>(101, -1));
        function<bool(int, int)> check = [&](int i, int j) -> bool {
            if (i > j) return false;
            int &v = f[i][j] = 0;
            if (i == j && s[i] == '*') return v = true;
            if (i == j && s[i] != '*') return v = false;
            if ((i + 1 == j) && (s[i] == '(' || s[i] == '*') && (s[j] == ')' || s[j] == '*')) {
                return true;
            }
            if ((s[i] == '(' || s[i] == '*') && (s[j] == ')' || s[j] == '*')) {
                v = v || check(i + 1, j - 1);
            }
            if (s[i] == '*') {
                v = v || check(i + 1, j);
            }
            if (s[j] == '*') {
                v = v || check(i, j - 1);
            }
            return v;
        };
        return check(0, s.size() - 1);
    }
};

int main() {
    auto s = Solution();
    cout << s.checkValidString("(*))") << "res: 1" << endl;
    cout << s.checkValidString("()") << "res: 1" << endl;
    cout << s.checkValidString("(*)") << "res: 1" << endl;
    cout << s.checkValidString(")(") << "res: 0" << endl;
    cout << s.checkValidString("((((()(()()()*()(((((*)()*(**("
                               "())))))(())()())(((())())())))))))(((((())*)))()))(()((*()*(*)))(*)()") << "res: 1"<<endl;
}