#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <numeric>
#include <cstring>
#include <queue>
#include <string>
#include <cmath>

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

using ll = long long;
using PII = pair<int, int>;
static constexpr int INF = 0x3f3f3f3f;
static constexpr int MOD = 998244353;
static constexpr int N = 32100, M = 32000;

int n;
int tr[N];

inline int lowbit(int x) {
    return x & (-x);
}

inline void add(int x, int c) {
    for (int pos = x; pos <= M; pos += lowbit(pos)) {
        tr[pos] += c;
    }
}

inline int query(int x) {
    int res = 0;
    for (int pos = x; pos; pos -= lowbit(pos)) {
        res += tr[pos];
    }
    return res;
}
int ans[N];
int main() {
    fhj();
    cin >> n;
    int x, y;
    memset(tr, 0, sizeof tr);
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        ++x;
        ans[query(x)]++;
        add(x, 1);
    }
    for(int i = 0; i < n; ++i){
        cout << ans[i] << endl;
    }
    return 0;
}