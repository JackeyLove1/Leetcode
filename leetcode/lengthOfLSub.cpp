#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

bool isUnique(string strs) {
    unordered_map<char, int> hash;
    for (auto str : strs) {
        if (hash.find(str) == hash.end())
            hash[str] = 1;
        else
            return false;
    }
    return true;
}

int lengthOfLongestSubstring(string s) {
    if (s.empty())return 0;
    int length = 1;
    for (int i = 0; i < s.size(); i++) {
        for (int j = 1; j <= s.size() - i; j++) {
            string tmp = s.substr(i, j);
            if (isUnique(tmp)) {
                length = max(length, j);
            } else
                break;
        }
    }
    return length;
}

int main() {
    cout << lengthOfLongestSubstring("abcabcbb") << endl;
    cout << lengthOfLongestSubstring("bbb") << endl;
    cout << lengthOfLongestSubstring("pwwkew") << endl;
    cout << lengthOfLongestSubstring("au") << endl;
    return 0;
}