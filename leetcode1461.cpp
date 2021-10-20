class Solution {
public:
    bool hasAllCodes(string s, int k) {
        unordered_map<string, int> m;
        for (int i = 0, len = k; i + len - 1 < s.size(); ++i) {
            string sub = s.substr(i, len);
            ++m[sub];
        }
        return m.size() == (1 << k);
    }
};
