class Solution {
public:
    string minRemoveToMakeValid(string s) {
        vector<int> num;
        vector<bool> st(s.size(), true);
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                num.push_back(i);
            }
            if (s[i] == ')') {
                if (!num.empty() && s[num.back()] == '(') {
                    num.pop_back();
                } else {
                    num.push_back(i);
                }
            }
        }
        for (auto &n : num) {
            st[n] = false;
        }
        string res = "";
        for (int i = 0; i < s.size(); ++i) {
            if (st[i]) res += s[i];
        }
        return res;
    }
};