class Solution {
public:
    int removePalindromeSub(const string &s) {
        bool flag = true;
        for (int i = 0, j = s.size() - 1; i < j && flag; ++i, --j) {
            if (s[i] != s[j]) flag = false;
        }
        if (flag) return 1;
        return 2;
    }
};