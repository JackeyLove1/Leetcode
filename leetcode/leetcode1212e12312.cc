class Solution {
public:
    string mergeAlternately(string &word1, string &word2) {
        string res{};
        int i = 0;
        for (; i < word1.size() && i < word2.size(); ++i) {
            res.push_back(word1[i]);
            res.push_back(word2[i]);
        }
        if (i < word1.size()) {
            res.append(word1.substr(i, word1.size() - i));
        }
        if (i < word2.size()) {
            res.append(word2.substr(i, word2.size() - i));
        }
        return res;
    }
};

