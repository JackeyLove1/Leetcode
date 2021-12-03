#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

constexpr int N = 110, M = 1e5;

class Solution {
    const int debug = 0;
public:
    bool isAdditiveNumber(string num) {
        std::function<bool(int, int, int)> dfs = [&](int num1, int num2, int cur) -> bool {
            bool v = false;
            for (int len = 1; cur + len - 1 < num.size(); ++len) {
                string s = num.substr(cur, len);
                if (stoi(s) == num1 + num2) {
                    if (debug) {
                        cout << "s: " << s << endl;
                        cout << "pos: " << cur + len << endl;
                    }
                    if (cur + len == num.size()) {
                        return true;
                    }
                    v = v || dfs(num2, num1 + num2, cur + len);
                }
            }
            return v;
        };
        bool res = false;
        for (int i = 0; i < num.size() - 1; ++i) {
            for (int j = i + 1; j < num.size() - 1; ++j) {
                for (int len = 1; len + j - 1 < num.size() - 1; ++len) {
                    string s1 = num.substr(i, j - i);
                    string s2 = num.substr(j, len);
                    if ((s1.size() > 1 && s1[0] == '0') || (s2.size() > 1 && s2[0] == '0')) continue;
                    int num1 = stoi(s1), num2 = stoi(s2);
                    if (debug) {
                        cout << "num1: " << num1 << endl;
                        cout << "num2: " << num2 << endl;
                        cout << "pos: " << j + len << endl;
                    }
                    res = res || dfs(num1, num2, j + len);
                }
            }
        }
        return res;
    }
};

int main() {
    auto s = Solution();
    cout << s.isAdditiveNumber("112358") << " res: 1" << endl;
    cout << s.isAdditiveNumber("199100199") << " res: 1" << endl;
    cout << s.isAdditiveNumber("1023") << " res: 0" << endl;
    return 0;
}