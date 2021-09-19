// Author: Jacky
// Time: 2021-09-18
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for (auto &n : num) {
            cout << n << " ";
        }
        cout << endl;
    }
    // cout << "ending ... " << endl;
}

constexpr int N = 1e6 + 100;
int d[N];

int main() {
    int n, p, h, m;
    cin >> n >> p >> h >> m;
    using PII = pair<int, int>;
    map<PII, bool> s;
    while (m--) {
        int a, b;
        cin >> a >> b;
        if (a > b) swap(a, b);
        if (s.count({a, b})) continue;
        s[{a,b}] = true;
        --d[a + 1], ++d[b];
    }
    for (int i = 1; i <= n; ++i) {
        d[i] += d[i - 1];
        cout << d[i] + h << endl;
    }
    return 0;
}