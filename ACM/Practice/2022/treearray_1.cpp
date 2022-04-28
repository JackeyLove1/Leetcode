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
static constexpr int N = 100010, M = 350;

int atr[N];
int btr[N][N];
int n, m;
namespace tr1 {
    // 单点修改+区间查询
    inline int lowbit(int x) {
        return x & (-x);
    }

    inline void add(int x, int y, int c) {
        for (int i = x; i <= n; i += lowbit(i)) {
            for (int j = y; j <= n; j += lowbit(j)) {
                btr[i][j] += c;
            }
        }
    }

    inline int ask(int x, int y) {
        int res = 0;
        for (int i = x; i; i -= lowbit(i)) {
            for (int j = y; j; j -= lowbit(j)) {
                res += btr[i][j];
            }
        }
        return res;
    }
}

namespace tr2 {
    // 区间修改+单点查询
    inline int lowbit(int x) {
        return x & (-x);
    }

    inline void add(int x, int c) {
        for (int i = x; i <= n; i += lowbit(x)) {
            atr[i] += c;
        }
    }

    inline void real_add(int l, int r, int c) {
        add(l, c);
        add(r + 1, -c);
    }

    inline int ask(int x) {
        int res = 0;
        for (int i = x; i; i -= lowbit(i)) {
            res += atr[i];
        }
        return res;
    }
}

namespace tr3 {
    // 二维的区间修改+单点查询可以用类似二维差分的方法来解决
    inline int lowbit(int x) {
        return x & (-x);
    }

    inline void add(int x, int y, int c) {
        for (int i = x; i <= n; i += lowbit(i)) {
            for (int j = y; j <= n; j += lowbit(j)) {
                btr[i][j] += c;
            }
        }
    }

    inline void real_add(int x1, int y1, int x2, int y2, int c) {
        add(x1, y1, c);
        add(x1, y2 + 1, -c);
        add(x2 + 1, y1, -c);
        add(x2 + 1, y2 + 1, c);
    }

    inline int ask(int x, int y) {
        int res = 0;
        for (int i = x; i <= n; i += lowbit(i)) {
            for (int j = y; j <= n; j += lowbit(j)) {
                res += btr[i][j];
            }
        }
        return res;
    }
}

namespace tr4 {
    // 一维区间修改+区间查询
    int sum1[N], sum2[N];

    inline int lowbit(int x) {
        return x & (-x);
    }

    inline void add(int x, int c) {
        for (int i = x; i <= n; i += lowbit(i)) {
            sum1[i] += c;
            sum2[i] += i * c;
        }
    }

    inline void readl_add(int x, int y, int c) {
        add(x, c);
        add(y + 1, -c);
    }

    inline int ask(int x) {
        int res = 0;
        for (int i = x; i; i -= lowbit(i)) {
            res += (i + 1) * sum1[i] - sum2[i];
        }
        return res;
    }

    inline int read_ask(int x, int y) {
        return ask(y) - ask(x - 1);
    }
}