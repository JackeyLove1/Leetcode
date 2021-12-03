//
// Created by Jacky on 2021/12/1.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>
#include <unordered_map>
#include <map>
#include <numeric>

using namespace std;

class Solution {
public:
    int numOfSubarrays(vector<int> &arr, int k, int threshold) {
        using ll = long long;
        ll target_sum = k * threshold;
        ll sub_sum = accumulate(arr.begin(), arr.begin() + k, 0);
        int l = 1, r = k;
        int res = sub_sum >= target_sum ? 1 : 0;
        for (; r < arr.size(); ++r, ++l) {
            sub_sum += static_cast<ll>(-arr[l-1] + arr[r]);
            res = sub_sum >= target_sum ? res + 1 : res;
        }
        return res;
    }
};

int main(){
    Solution s;
    vector<int> nums = {11,13,17,23,29,31,7,5,2,3};
    cout << s.numOfSubarrays(nums, 3, 5) << endl;
}