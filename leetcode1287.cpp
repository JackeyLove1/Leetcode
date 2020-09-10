#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

int findSpecialInteger(vector<int>& arr) {
    int n = arr.size();
    unordered_map<int, int>hash;
    for(auto num : arr){
        hash[num]++;
        if(hash[num] > n/4)
            return num;
    }
    return -1;
}