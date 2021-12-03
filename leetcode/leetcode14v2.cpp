#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <functional>
#include <queue>
#include <set>

using namespace std;

string longestCommonPrefix(vector<string> &strs) {
    for (auto &str : strs) {
        if (str.empty()) return "";
    }
    int n = strs[0].size();
    int len;
    bool flag = true;
    for (len = 0; len < n && flag; len++) {
        for (auto &str : strs) {
            if (len > str.size() || str[len] != strs[0][len]) {
                flag = false;
                len--;
                break;
            }
        }
    }
    return strs[0].substr(0, len);
}