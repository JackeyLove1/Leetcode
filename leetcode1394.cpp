#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>

using namespace std;

int findLucky(vector<int>& arr) {
    unordered_map<int, int>hash;
    for(auto num:arr){
        if(hash.find(num) == hash.end())
            hash[num] = 1;
        else
            hash[num]++;
    }
    int res = -1;
    for(auto it = hash.begin();it != hash.end(); it++){
        if(it->first == it->second)
            res = max(res, it->first);
    }
    return res;
}