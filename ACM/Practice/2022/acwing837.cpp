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

int n, m;
int p[N], cnt[N];

inline int find(int x) {
    if (x != p[x]) return p[x] = find(p[x]);
    return p[x];
}

inline void merge(int a, int b) {
    int pa = find(a), pb = find(b);
    if (pa != pb) {
        p[pa] = pb;
        cnt[pb] += cnt[pa];
    }
}

inline int query(int x) {
    return cnt[find(x)];
}


int main() {
    fhj();
    cin >> n >> m;
    // initialize
    for (int i = 0; i < n; ++i) {
        p[i] = i, cnt[i] = 1;
    }
    int a, b;
    string op;
    while (m--) {
        cin >> op;
        if (op == "C") {
            cin >> a >> b;
            merge(a, b);
        } else if (op == "Q1") {
            cin >> a >> b;
            string res = (find(a) == find(b)) ? "Yes" : "No";
            cout << res << endl;
        } else {
            cin >> a;
            cout << query(a) << endl;
        }
    }
    return 0;
}