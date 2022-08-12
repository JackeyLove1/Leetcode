class Solution {
public:
    vector<vector<int>> groupThePeople(vector<int>& groupSizes) {
        vector<vector<int>> res;
        map<int, vector<vector<int>>> mp;
        for(int i = 0; i < groupSizes.size(); ++i){
            if (mp.find(groupSizes[i]) == mp.end()){
                mp[groupSizes[i]].push_back({i});
            }else{
                bool flag = false;
                for(auto& vec : mp[groupSizes[i]]){
                    if (vec.size() < groupSizes[i]){
                        vec.push_back(i);
                        flag = true;
                        break;
                    }
                }
                if (!flag){
                    mp[groupSizes[i]].push_back({i});
                }
            }
        }
        for(auto& [_, vec] : mp){
            for(auto& v : vec){
                res.emplace_back(std::move(v));
            }
        }
        return res;
    }
};