#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
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

inline int cnt(int x) {
    return __builtin_popcount(x);
}

static constexpr int N = 12, M = 1 << 10, K = 110;
static constexpr int INF = 0x3f3f3f3f;
static constexpr int MOD = 1e7 + 7;
using ll = long long;
int n, m;

int main() {
    fhj();
    cin >> n >> m;
    int res = n;
    int cnt = 0;
    while (res) {
        ++cnt;
        if (cnt % m == 0) ++res;
        --res;
    }
    cout << cnt << endl;
    return 0;
}