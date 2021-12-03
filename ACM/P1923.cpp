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

int main() {
    fhj();
    int n, m;
    cin >> n >> m;
    vector<int> g;
    int x;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        g.push_back(x);
    }
    nth_element(g.begin(), g.begin() + m, g.end());
    cout << g[m] << endl;
    return 0;
}