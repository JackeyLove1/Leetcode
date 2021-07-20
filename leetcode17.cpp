#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <functional>
#include <queue>
#include <set>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for (auto &num : nums) cout << num << " ";
    cout << endl;
}

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for (auto &n : num) {
            cout << n << " ";
        }
        cout << endl;
    }
    cout << "ending .... " << endl;
}

int maxArea(vector<int>& height) {
    if(height.empty()) return 0;
    int l = 0, r = height.size() - 1;
    int res = min(height[l], height[r]) * (r - l);
    while (l < r){
        int cur = min(height[l], height[r]) * (r - l);
        res = max(res, cur);
        if(height[l] < height[r]){
            l++;
        }else{
            r--;
        }
    }
    return res;
}