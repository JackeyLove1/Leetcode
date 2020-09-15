#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

int findLowerNumber(vector<int> &nums, int x) {
    int cnt = 0;
    if (x < 0) return cnt;
    auto it = upper_bound(nums.begin(), nums.end(), x);
    cnt = int(it - nums.begin());
    return cnt;
}

int breakfastNumber(vector<int> &staple, vector<int> &drinks, int x) {
    sort(drinks.begin(), drinks.end());
    int res = 0;
    for (auto st : staple) {
        res = (res + findLowerNumber(drinks, x - st)) % 1000000007;
    }
    return res;
}