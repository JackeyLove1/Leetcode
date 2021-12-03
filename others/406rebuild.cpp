#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

static bool cmp(vector<int> &v1, vector<int> &v2) {
    if (v1[0] != v2[0])
        return v1[0] > v2[0];
    return v1[1] < v2[1];
}

vector<vector<int>> reconstructQueue(vector<vector<int>> &people) {
    if(people.empty()) return people;
    sort(people.begin(), people.end(), cmp);
    vector<vector<int>> res;
    for(auto p : people){
        auto pos = res.begin();
        advance(pos, p[1]);
        res.insert(pos, p);
    }
    return res;
}