#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ll = long long;

static constexpr int N = 1e5 + 100;
vector<int> a, b;
int nums[N];

int main() {
    fhj();
    int n, m;
    cin >> n >> m;
    a.reserve(n), b.reserve(m);
    for (int i = 0; i < n + m; ++i) {
        cin >> nums[i];
    }
    int flag;
    for (int i = 0; i < n + m; ++i) {
        cin >> flag;
        if (flags[i]) {
            b.push_back(nums[i]); // trash
        } else {
            a.push_back(nums[i]); // person
        }
    }
    unordered_map<int, int> cnt;
    for (int i = 0; i < n; ++i) {
        // find greater
        auto it = upper_bound(b.begin(), b.end(), a[i]);
        if (it == b.end()) {
            cnt[b.back()] += 1;
            continue;
        }
        if (it == b.begin()) {
            cnt[b.front()] += 1;
            continue;
        }
        int right = *it;
        int left = *(--it);
        if (right - a[i] >= a[i] - left) {
            cnt[left] += 1;
        } else {
            cnt[right] += 1;
        }
    }
    for (int i = 0; i < b.size(); ++i) {
        if (cnt.count(b[i])) {
            cout << cnt[b[i]] << " ";
        } else {
            cout << 0 << " ";
        }
    }
    return 0;
}