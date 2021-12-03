#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <functional>
#include <map>
#include <set>
#include <string>

using namespace std;


int numIdenticalPairs(vector<int> &nums) {
    map<int, int> hash;
    for (int i = 0; i < nums.size(); i++) {
        hash[nums[i]]++;
    }
    int res = 0;
    for (auto it = hash.begin(); it != hash.end(); it++) {
        int n = it->second;
        res += n * (n - 1) / 2;
    }
    return res;
}