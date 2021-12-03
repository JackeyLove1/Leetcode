#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <numeric>
#include <cmath>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    int peakIndexInMountainArray(vector<int> &arr) {
        int res = 0, target = arr[0];
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] > target) {
                target = arr[i];
                res = i;
            }else{
                break;
            }
        }
        return res;
    }
};