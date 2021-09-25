// Author: Jacky
// Time: 2021-09-24
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

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

int n, m;
constexpr int N = 3000;
using PII = pair<int, int>;
PII cows[N];

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> cows[i].first >> cows[i].second;
    }
    map<int, int> spf;
    int kind, cover;
    for (int i = 0; i < m; ++i) {
        cin >> kind >> cover;
        spf[kind] += cover;
    }
    sort(cows, cows + n);
    int res = 0;
    spf[0] = spf[1001] = n;
    for (int i = n - 1; i >= 0; --i) {
        auto iter = spf.upper_bound(cows[i].second);
        --iter;
        if (iter->first >= cows[i].first) {
            ++res;
            if(--iter->second == 0){
                spf.erase(iter);
            }
        }
    }
    cout << res << endl;
    return 0;
}