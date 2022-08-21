class Solution {
public:
    string kthDistinct(vector<string> &arr, int k) {
        map<string, int> mp;
        for (const auto &str: arr) {
            ++mp[str];
        }
        for (const auto &str: arr) {
            if (mp[str] == 1 && --k == 0) {
                return str;
            }
        }
        return "";
    }
};