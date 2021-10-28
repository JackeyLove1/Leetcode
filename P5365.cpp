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

constexpr int N = 1000010;
int n, m;
int nums[N], cost[N];
ll f[N];

int main() {
    fhj();
    cin >> n >> m;
    ll sum = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> nums[i];
    
    }
    for (int i = 1; i <= n; ++i) {
        cin >> cost[i];
        sum += nums[i] * cost[i];
    }
    f[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = sum; j >= 0; --j) {
            for (int k = 0; k <= nums[i] && k * cost[i] <= j; ++k) {
                f[j] = max(f[j], f[j - k * cost[i]] * k);
            }
        }
    }
    int res = 0;
    while (res <= sum && f[res] < m) ++res;
    cout << res << endl;
    return 0;
}