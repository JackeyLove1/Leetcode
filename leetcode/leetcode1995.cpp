#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <cstring>
#include <cmath>
#include <list>
#include <atomic>
#include <cstring>
#include <cstdlib>
#include <tuple>

using namespace std;

template<typename T>
static inline void print(vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    int countQuadruplets(vector<int> &nums) {
        // set<tuple<int, int, int, int>> s;
        // sort(nums.begin(), nums.end());
        int res = 0;
        for(int i = 0; i < nums.size(); ++i){
            for(int j = i + 1; j < nums.size(); ++j){
                for(int k = j + 1; k < nums.size(); ++k){
                    for(int l = k + 1; l < nums.size(); ++l){
                        if (nums[i] + nums[j] + nums[k] == nums[l]){
                            ++res;
                        }
                    }
                }
            }
        }
        return res;
    }
};