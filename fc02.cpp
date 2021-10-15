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

constexpr int N = 1e7 + 100;
int diff[N];

int main() {
    int n;
    cin >> n;
    int a, b, c;
    while (cin >> a >> b >> c && a && b) {
        diff[b + 1] -= c;
        diff[a] += c;
    }
    int res = INT_MIN;
    for (int i = 1; i <= n; ++i) {
        diff[i] += diff[i - 1];
        res = max(res, diff[i]);
        cout << diff[i] << "  ";
    }
    cout << res << endl;
    return 0;
}