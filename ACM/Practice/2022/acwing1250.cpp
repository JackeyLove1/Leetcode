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

using ll = long long;
using PII = pair<int, int>;
static constexpr int INF = 0x3f3f3f3f;
static constexpr int MOD = 998244353;
static constexpr int N = 40010 + 100, M = 3100010;

int n, m;
int p[N];

inline int find(int x) {
    if (x != p[x]) return p[x] = find(p[x]);
    return p[x];
}

// two dimensions -> one dimensions
inline void init() {
    for (int i = 0; i <= n * n; ++i) {
        p[i] = i;
    }
}

inline int get(int x, int y) {
    return x * n + y;
}

inline bool merge(int a, int b) {
    int pa = find(a), pb = find(b);
    if (pa == pb) return true;
    p[pa] = pb;
    return false;
}

int main() {
    fhj();
    cin >> n >> m;
    init();
    int res = -1;
    for (int i = 1; i <= m; ++i) {
        int l, r;
        char op;
        cin >> l >> r >> op;
        --l,--r;
        int l1 = l, r1 = r;
        if (op == 'D') ++l1;
        if (op == 'R') ++r1;
        int a = get(l, r), b = get(l1, r1);
        if (merge(a, b)) {
            res = i;
            break;
        }
    }
    if (res == -1) cout << "draw" << endl;
    else cout << res << endl;
    return 0;
}