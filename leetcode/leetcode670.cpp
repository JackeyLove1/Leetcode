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

class TreeNode {
public:
    int val;
    TreeNode *right, *left;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int val_) : val(val_), left(nullptr), right(nullptr) {}

};

class Solution {
public:
    int maximumSwap(int num) {
        vector<int> nums;
        while (num) {
            nums.push_back(num % 10);
            num /= 10;
        }
        reverse(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() ; ++i) {
            int maxNum = nums[i], maxIndex = i;
            for (int j = nums.size() - 1; j > i; --j) {
                if (nums[j] > maxNum) {
                    maxNum = nums[j];
                    maxIndex = j;
                }
            }
            if (maxIndex != i) {
                swap(nums[i], nums[maxIndex]);
                break;
            }
        }
        int res = 0;
        for (const int val : nums) {
            res = res * 10 + val;
        }
        return res;
    }
};

int main() {
    Solution s;
    cout << s.maximumSwap(2736) << " res: 7236" << endl;
    cout << s.maximumSwap(9973) << " res: 9973" << endl;
    cout << s.maximumSwap(98368) << " res: 98863" << endl;
    cout << s.maximumSwap(1993) << " res: 9913" << endl;
}