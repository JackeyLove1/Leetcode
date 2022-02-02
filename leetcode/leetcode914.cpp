#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
private:
    int gcd(int a, int b) {
        if (b == 0) return a;
        return gcd(b, a % b);
    }

public:
    bool hasGroupsSizeX(const vector<int> &deck) {
        unordered_map<int, int> mp;
        for (const int num : deck) {
            mp[num]++;
        }
        vector<int> nums;
        nums.reserve(mp.size());
        for (const auto&[_, v] : mp) {
            nums.push_back(v);
        }
        if (nums.size() == 1) return deck.size() > 1;
        int q = gcd(nums[0], nums[1]);
        if (q == 1) return false;
        for (int i = 1; i < nums.size(); ++i) {
            if (gcd(nums[i], nums[0]) != q) return false;
        }
        return true;
    }
};

int main() {
    Solution s;
    vector<int> nums = {1, 1, 2, 2, 2, 2};
    cout << s.hasGroupsSizeX(nums) << " res: 1" << endl;
    vector<int> v2 = {1, 1, 1, 1, 2, 2, 2, 2, 2, 2};
    cout << s.hasGroupsSizeX(v2) << " res: 1" << endl;
    vector<int> v3 = {1, 1};
    cout << s.hasGroupsSizeX(v3) << " res: 1" << endl;
    return 0;
}