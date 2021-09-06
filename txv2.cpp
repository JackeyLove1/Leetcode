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
#include <cmath>

using namespace std;

constexpr int N = 1e6 + 100;
int a[N], b[N];
unordered_map<int, int> cache;

int n;

inline void cal(int x) {
    if (cache.count(x)) return;
    int sq = sqrt(x);
    int res = 0;
    for (int i = 1; i <= sq; i++) {
        if (i != sq && x % i == 0) res += 2;
        if (i == sq && (sq * sq == x)) res += 1;
        if (i == sq && x % sq == 0 && (x / sq != sq)) res += 2;
    }
    cache[x] = res;
    // cout << "x: " << x << " cache: " << cache[x] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        cal(a[i]);
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
        cal(b[i]);
    }
    auto f = [&](const int x, const int y) {
        return cache[x] < cache[y];
    };
    sort(a, a + n, f);
    sort(b, b + n, f);
    int idx1 = 0, idx2 = 0, res = 0;
    while (idx1 < n && idx2 < n) {
        if (cache[a[idx1]] <= cache[b[idx2]]) {
            ++idx1;
        } else {
            ++res, ++idx1, ++idx2;
        }
    }
    cout << res << endl;
    return 0;
}