class Solution {
public:
    vector<string> divideString(const string &s, int k, char fill) {
        vector<string> res;
        int st = 0;
        while (st < s.size()) {
            res.push_back(s.substr(st, k));
            st += k;
        }
        while (res.back().size() < k) {
            res.back().push_back(fill);
        }
        return res;
    }
};