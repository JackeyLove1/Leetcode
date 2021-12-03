#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;


vector<vector<int> > permuteUnique(vector<int> &nums) {
    vector<vector<int> > res;
    sort(nums.begin(), nums.end());
    res.emplace_back(nums);
    while (next_permutation(nums.begin(), nums.end()))
        res.emplace_back(nums);
    return res;
}