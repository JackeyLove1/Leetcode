#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <unordered_set>


using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;
constexpr int N = 1e6 + 1000, M = 1e5 + 100;
int a[N];
vector<int> p, t;

int find_low(vector<int> &v, int l, int r, int target) {
    while (l < r) {
        int mid = l + r + 1 >> 1;
        if (v[mid] <= target) l = mid;
        else r = mid - 1;
    }
    return l;
}

int find_high(vector<int> &v, int l, int r, int target) {
    while (l < r) {
        int mid = l + r >> 1;
        if (v[mid] >= target) r = mid;
        else l = mid + 1;
    }
    return l;
}

int main() {
    fhj();
    int n, m;
    cin >> n >> m;
    p.reserve(n), t.reserve(m);
    for (int i = 0; i < n + m; ++i) {
        cin >> a[i];
    }
    int flag;
    for (int i = 0; i < n + m; ++i) {
        cin >> flag;
        if (flag) {
            t.push_back(a[i]);
        } else {
            p.push_back(a[i]);
        }
    }
    sort(p.begin(), p.end());
    sort(t.begin(), t.end());
    unordered_map<int, int> um;
    for (const auto num: p) {
        auto l = find_low(t, 0, t.size() - 1, num);
        auto r = find_high(t, 0, t.size() - 1, num);
        if (std::abs(t[l] - num) > std::abs(t[r] - num)) ++um[t[r]];
        else ++um[t[l]];
        // cout <<"num: " << num <<" l:" << t[l] <<" r: " << t[r] << endl;
    }
    for (const auto num: t) {
        cout << um[num] << " ";
    }
    return 0;
}