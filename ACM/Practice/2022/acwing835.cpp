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
static constexpr int N = 1e5 + 100, M = 1e6 + 100;
using ll = long long;
using PII = pair<int, int>;
#define x first
#define y second

int n, m;
int son[N][26], cnt[N], idx;

inline void insert(string &strs) {
    int p = 0;
    for (const auto &ch : strs) {
        int u = ch - 'a';
        if (!son[p][u]) son[p][u] = ++idx;
        p = son[p][u];
    }
    cnt[p]++;
}

inline int query(string &strs) {
    int p = 0;
    for (const auto &ch : strs) {
        int u = ch - 'a';
        if (!son[p][u]) return 0;
        p = son[p][u];
    }
    return cnt[p];
}

int main() {
    fhj();
    cin >> n;
    char op;
    string strs;
    for (int i = 0; i < n; ++i) {
        cin >> op >> strs;
        if (op == 'I') {
            insert(strs);
        } else {
            cout << query(strs) << endl;
        }
    }
    return 0;
}