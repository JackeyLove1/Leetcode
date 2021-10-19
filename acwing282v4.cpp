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


int n;
constexpr int N = 400;
int nums[N], s[N];
int f[N][N];

int solve(int l, int r) {
    if (l == r) return 0;
    int &v = f[l][r];
    if (v != -1) return v;
    v = 1e9;
    for (int k = l; k < r; ++k) {
        v = min(v, solve(l, k) + solve(k + 1, r) + s[r] - s[l - 1]);
    }
    return v;
}

int main() {
    fhj();
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> nums[i];
        s[i] = s[i - 1] + nums[i];
    }
    memset(f, -1, sizeof f);
    cout << solve(1, n) << endl;
    return 0;
}