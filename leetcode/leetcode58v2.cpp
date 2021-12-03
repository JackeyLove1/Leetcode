class Solution {
public:
    int lengthOfLastWord(string s) {
        if (s.empty()) return 0;
        while (!s.empty() && s.back() == ' ') s.pop_back();
        int len = 0;
        for (auto it = s.rbegin(); it != s.rend(); ++it) {
            if (*it == ' ') break;
            ++len;
        }
        return len;
    }
};