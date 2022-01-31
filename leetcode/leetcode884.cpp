class Solution {
private:
    inline unordered_map<string, int> split(const string &lines) {
        istringstream str(lines);
        string out;
        unordered_map<string, int> outs;
        while (str >> out) {
            outs[out]++;
        }
        return outs;
    }

public:
    vector<string> uncommonFromSentences(const string &s1, const string &s2) {
        auto words1 = split(s1);
        auto words2 = split(s2);
        vector<string> res;
        for (const auto &[word, cnt] : words1) {
            if (cnt == 1 && !words2.count(word)) {
                res.push_back(word);
            }
        }
        for (const auto &[word, cnt] : words2) {
            if (cnt == 1 && !words1.count(word)) {
                res.push_back(word);
            }
        }
        return res;
    }
};