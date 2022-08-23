class Solution {
public:
    bool uniqueOccurrences(vector<int> &arr) {
        map<int, int> mp;
        for (const int num: arr) {
            ++mp[num];
        }
        set<int> s;
        for (const auto &[_, v]: mp) {
            s.insert(v);
        }
        return s.size() == mp.size();
    }
};