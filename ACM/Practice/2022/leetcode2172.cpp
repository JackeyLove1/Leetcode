#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <unordered_set>
#include <numeric>
#include <cstring>
#include <queue>
#include <string>
#include <climits>

using namespace std;

template<typename T>
static inline void print(vector<T> &vec) {
    for_each(vec.begin(), vec.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

inline int cnt(int x) {
    return __builtin_popcount(x);
}

constexpr int N = 2200, M = 550;
using ll = long long;
int f[N][N];
constexpr int INF = 0x3f3f3f3f;
int n, m;
int a[N];

class Solution {
public:
    int maximumANDSum(vector<int> &nums, int numSlots) {
        int n = nums.size();
        int mask_max = 1;
        for (int i = 0; i < numSlots; ++i) {
            mask_max *= 3;
        }
        vector<int> f(mask_max, 0);
        std::function<int(int)> count = [](int mask) -> int {
            int cnt = 0;
            while (mask) {
                cnt += mask % 3;
                mask /= 3;
            }
            return cnt;
        };
        for (int mask = 0; mask < mask_max; ++mask) {
            int cnt = count(mask);
            if (cnt > n) continue;
            for (int i = 0, dummy = mask, w = 1; i < numSlots; ++i, dummy /= 3, w *= 3) {
                if (dummy % 3) {
                    f[mask] = max(f[mask], f[mask - w] + (nums[cnt - 1] & (i + 1)));
                }
            }
        }
        return *max_element(f.begin(), f.end());
    }
};

