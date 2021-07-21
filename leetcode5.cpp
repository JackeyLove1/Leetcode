#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <queue>
#include <set>

using namespace std;


// 优化暴力破解
bool isPalindrome(string &s) {
    if (s.size() <= 1) return true;
    for (int i = 0, j = s.size() - 1; i < j; i++, j--) {
        if (s[i] != s[j]) return false;
    }
    return true;
}

string longestPalindrome(string s) {
    if (s.empty()) return "";
    int n = s.size();
    string res = s.substr(0, 1);
    for (int i = 0; i < n; i++) {
        int l = i, r = n - 1;
        for (; r > l; r--) {
            if (s[r] != s[l]) continue;
            else {
                string tmp = s.substr(l, r - l + 1);
                if (isPalindrome(tmp)) {
                    if (tmp.size() > res.size()) res = tmp;
                    break;
                }
            }
        }
    }
    return res;
}

int main(){
    cout << longestPalindrome("babad")<< " res:bab"<<endl;
    cout << longestPalindrome("cbbd")<< " res:bb"<<endl;
    cout << longestPalindrome("a")<< " res:a"<<endl;
}