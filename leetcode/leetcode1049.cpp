#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <numeric>
#include <cmath>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    int lastStoneWeightII(vector<int> &stones) {
        int sum = accumulate(stones.begin(), stones.end(), 0);
        int target = sum >> 1, n = stones.size();
        // vector<vector<int>> f(n + 1, vector<int>(target + 1, 0));
        vector<int> f(target + 1, 0);
        for (auto &stone : stones) {
            for (int j = target; j >= stone; j--) {
                f[j] = max(f[j], f[j - stone] + stone);
            }
        }
        return sum - 2 * f[target];
    }
};

int main() {

}