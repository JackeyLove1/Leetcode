// Author: Jacky
// Date: 2021-09-29
#include <iostream>
#include <vector>
#include <algorithm>
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

constexpr int N = 1e3;
int g[N];

int main() {
    fhj();
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int x;
        cin >> x;
        ++g[x];
    }
    for (int i = 1; i <= n; ++i) {
        while (g[i]--) {
            cout << i << ' ';
        }
    }
    return 0;
}