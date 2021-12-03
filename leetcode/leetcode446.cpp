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
    int numberOfArithmeticSlices(vector<int> &nums) {
        using ll = long long;
        int n = nums.size();
        int res = 0;
        vector<unordered_map<ll, int>> f(n + 1);// diff -> cnt
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                ll d = 1ll * nums[i] - nums[j];
                // cout << d << endl;
                auto it = f[j].find(d);
                int cnt = it == f[j].end() ? 0 : it->second;
                res += cnt;
                // cout << res << endl;
                f[i][d] += cnt + 1;
            }
        }
        return res;
    }
};

int main() {
    vector<int> nums = {2, 4, 6, 8, 10};
    auto s = Solution();
    cout << s.numberOfArithmeticSlices(nums) << " res: 7" << endl;
    return 0;
}