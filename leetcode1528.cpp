#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <string>

using namespace std;

string restoreString(string s, vector<int> &indices) {
    vector<char> chars(s.size(), 'a');
    for (int i = 0; i < indices.size(); i++) {
        chars[indices[i]] = s[i];
    }
    string res = "";
    for (auto ch : chars)
        res += ch;
    return res;
}