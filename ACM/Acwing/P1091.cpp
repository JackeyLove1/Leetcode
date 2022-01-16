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

constexpr int N = 110;
int n;
int f[N], g[N], s[N];

int main() {
    fhj();
    cin >> n;
    fill(f + 1, f + n + 1, 1);
    fill(g + 1, g + n + 1, 1);
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j < i; ++j) {
            if (s[i] > s[j]) f[i] = max(f[i], f[j] + 1);
        }
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j < i; ++j) {
            if (s[i] < s[j]) g[i] = max(g[i], g[j] + 1);
        }
    }
    int maxn = 0;
    for (int i = 1; i <= n; ++i) {
        maxn = max(maxn, f[i] + g[i] - 1);
    }
    cout << n - maxn << endl;
    return 0;
}