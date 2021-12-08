class Solution {
public:
    bool isPrefixString(string s, vector<string> &words) {
        string t;
        for(auto& word : words){
            t += word;
            if (t == s) return true;
        }
        return false;
    }
};