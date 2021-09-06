//
// Created by Jacky on 2021/9/5.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <unordered_map>
#include <list>

using namespace std;

constexpr int N = 1e5 + 100, INF = 1e6;
string s;
int n;
using ll = long long;
inline ll cal(int cnt) {
    return (1ll + cnt) * cnt / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    int left1 = INF, right1 = -INF;
    int left0 = INF, right0 = -INF;
    cin >> s;

    ll res = 1;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '1') {
            left1 = min(left1, i);
            right1 = max(right1, i);
        } else {
            left0 = min(left0, i);
            right0 = max(right0, i);
        }
    }
    // 左边全1，右边全0
    int one1 = 0, zero1 = 0;
    for (int i = left1; i <= right1; ++i) {
        if (s[i] == '1') ++one1;
    }
    for (int i = right1 + 1; i <= n; ++i) {
        if (s[i] == '0') ++zero1;
    }
    ll tmp1 = cal(one1) + cal(zero1);
    // 左边全0，右边全1
    int one2 = 0, zero2 = 0;
    for (int i = left0; i <= right0; ++i) {
        if (s[i] == '0') ++zero2;
    }
    for (int i = right0 + 1; i <= n; ++i) {
        if (s[i] == '1') ++one2;
    }
    ll tmp2 = cal(one2) + cal(zero2);
    res = max(tmp1, tmp2);
    cout << res << endl;
    return 0;
}