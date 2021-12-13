#include <unordered_map>
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

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    int minElements(vector<int> &nums, int limit, int goal) {
        using ll = long long;
        ll sum = 0;
        for(auto& num : nums) sum += static_cast<ll>(num);
        ll diff = ll(goal) - sum;
        diff = abs(diff);
        limit = abs(limit);
        if (diff % limit == 0) return static_cast<int>(diff / limit);
        return static_cast<int>(diff / limit) + 1;
    }
};

int main() {
    Solution s;
    vector<int> v1 = {1, -1, 1};
    cout << s.minElements(v1, 3, -4) << endl;

}