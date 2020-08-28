vector<vector<string>> groupAnagrams(vector<string> &strs) {
    vector<string> scopy;
    for (auto s : strs) {
        sort(s.begin(), s.end());
        scopy.push_back(s);
    }
    unordered_map<string, vector<string>> hash;
    for (int i = 0; i < strs.size(); i++) {
        if (hash.find(scopy[i]) == hash.end())
            hash[scopy[i]] = {};
        hash[scopy[i]].push_back(strs[i]);
    }
    vector<vector<string>> res;
    for (auto it = hash.begin(); it != hash.end(); ++it) {
        res.push_back(it->second);
    }
    return res;
}