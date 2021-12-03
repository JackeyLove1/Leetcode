#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<vector>

using namespace std;

class Solution {
public:
    void helper(string &s, int k) {
        if (s.size() < k) {
            reverse(s.begin(), s.end());
        } else {
            reverse(s.begin(), s.begin() + k);
        }
    }

    string reverseStr(string s, int k) {
        string res = "";
        int i = 0;
        for (; i + 2 * k <= s.size(); i += 2 * k) {
            string str = s.substr(i, 2 * k);
            helper(str, k);
            // cout << "str: " << str << endl;
            res += str;
        }
        string str = s.substr(i, 2 * k);
        helper(str, k);
        // cout << "str: " << str << endl;
        res += str;
        return res;
    }
};

int main() {
    auto s = Solution();
    cout << s.reverseStr("abcdefg", 2) << " res: bacdfeg" << endl;
    cout << s.reverseStr("abcd", 2) << " res: bacd" << endl;
    return 0;
}