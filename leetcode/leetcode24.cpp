#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>

using namespace std;

vector<int> singleNumber(vector<int>& nums) {
    unordered_map<int, int>hash;
    for(auto num :nums){
        if(hash.find(num) == hash.end())
            hash[num] = 1;
        else
            hash[num]++;
    }
    vector<int>res;
    for(auto it = hash.begin(); it != hash.end(); it++){
        if(it->second == 1)
            res.push_back(it->first);
    }
    return res;
}