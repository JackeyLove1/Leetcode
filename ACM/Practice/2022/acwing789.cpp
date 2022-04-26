#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <list>
#include <numeric>
#include <cstring>
#include <queue>
#include <string>
#include <climits>

using namespace std;

template<typename T>
static inline void print(vector<T> &vec) {
    for_each(vec.begin(), vec.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

static inline int cnt_(int x) {
    return __builtin_popcount(x);
}

static constexpr int INF = 0x3f3f3f3f;
static constexpr int MOD = 998244353;
static constexpr int N = 1e6 + 100, M = 3100010;
using ll = long long;
using PII = pair<int, int>;
int n, m;
int a[N];

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> a[i];
    int x, l, r, mid;
    while (m--) {
        cin >> x;
        l = 0, r = n - 1;
        // left
        while (l < r) {
            mid = l + r >> 1;
            if (a[mid] >= x) r = mid;
            else l = mid + 1;
        }
        int left = l;
        if (a[left] != x) {
            cout << "-1 -1" << endl;
        } else {
            l = 0, r = n - 1;
            while (l < r) {
                mid = l + r + 1 >> 1;
                if (a[mid] <= x) l = mid;
                else r = mid - 1;
            }
            int right = l;
            cout << left << " " << right << endl;
        }
    }
    return 0;
}