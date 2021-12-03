class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<string, int> m;
        vector<string> res;
        if(s.size() < 10) return res;
        for (int i = 0; i < s.size() - 9; i++) {
            auto str = s.substr(i, 10);
            if (++m[str] == 2) {
                res.emplace_back(str);
            }
        }
        return res;
    }
};