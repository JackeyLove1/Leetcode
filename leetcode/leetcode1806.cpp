// Author: Jacky
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>
#include <numeric>


using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

inline int count(int x) {
    return __builtin_popcount(x);
}

constexpr int N = 22, M = 35, INF = 0x3f3f3f3f;

class Solution {
public:
    int reinitializePermutation(int n) {
        vector<int> perm, v;
        for (int i = 0; i < n; ++i) {
            perm.push_back(i);
            v.push_back(i);
        }
        vector<int> arr(n);
        std::function<void()> f = [&]() {
            for (int i = 0; i < n; ++i) {
                if (!(i & 1)) arr[i] = perm[i / 2];
                else arr[i] = perm[n / 2 + (i - 1) / 2];
            }
            perm = arr;
        };
        int cnt = 1;
        f();
        while (perm != v) {
            ++cnt;
            f();
        }
        return cnt;
    }
};

int main() {
    auto s = Solution();
    cout << s.reinitializePermutation(2) << endl;
}