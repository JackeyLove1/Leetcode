class Solution {
public:
    int countSegments(string s) {
        istringstream str(s);
        string out;
        vector<string> res;
        while (str >> out) {
            res.push_back(out);
        }
        return res.size();
    }
};