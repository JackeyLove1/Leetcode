// Author: Jacky
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>
#include <numeric>


using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

inline int count(int x) {
    return __builtin_popcount(x);
}

constexpr int N = 1e6 + 100, M = 2e5 + 100, MOD = 1e9 + 7;
int d[N], in[N], out[N];
int h[N], e[N], ne[N], idx;

inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

inline void init() {
    idx = 0;
    memset(h, -1, sizeof h);
}

int n, m, ans;

inline void dfs() {
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (!in[i]) {
            q.push(i);
            d[i] = 1;
        }
    }
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            d[j] += d[t];
            if (--in[j] == 0) {
                if (out[j]) {
                    q.push(j);
                } else {
                    ans += d[j];
                }
            }
        }
    }
}

int main() {
    fhj();
    cin >> n >> m;
    int a, b;
    init();
    for (int i = 1; i <= m; ++i) {
        cin >> a >> b;
        add(a, b);
        ++out[a], ++in[b];
    }
    dfs();
    cout << ans << endl;
    return 0;
}