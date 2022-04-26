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
static constexpr int N = 100010, M = 3100010;
using ll = long long;
using PII = pair<int, int>;

static constexpr int P = 131;
using ULL = unsigned long long;
int n, m;
char str[N];
ULL h[N], p[N];

inline ULL get(int l, int r) {
    return h[r] - h[l-1] * p[r - l + 1];
}

int main() {
    cin >> n >> m;
    p[0] = 1;
    for (int i = 1; i <= n; ++i) {
        cin >> str[i];
        h[i] = h[i - 1] * P + str[i];
        p[i] = p[i - 1] * P;
    }
    while (m--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        if (get(l1, r1) == get(l2, r2)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }

    return 0;
}