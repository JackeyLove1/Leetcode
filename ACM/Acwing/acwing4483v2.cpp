#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unordered_map>
#include <cmath>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

static constexpr int N = 2e5 + 100;

int main() {
    fhj();
    int n, k;
    cin >> n >> k;
    vector<int> a;
    a.reserve(n);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        a.push_back(x);
    }
    sort(a.begin(), a.end());
    int res = n;
    for (int i = 0; i < n; ++i) {
        auto it = upper_bound(a.begin() + i, a.end(), a[i] + k);
        if (it == a.end() || it == a.begin()) {
            if (a.back() > a[i] && a.back() - a[i] <= k) {
                --res;
                continue;
            }
        }
        if (*(--it) > a[i])--res;
    }
    cout << res << endl;
    return 0;
}