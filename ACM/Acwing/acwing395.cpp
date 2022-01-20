#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stack>


#pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

inline int count(int state) {
    return __builtin_popcount(state);
}

constexpr int N = 5010, M = 20010;

int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
int id[N], dcc_cnt;
bool is_bridge[M];//每条边是不是桥
int d[N];//度数

inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void tarjan(int u, int from) {
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u;

    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j, i);
            low[u] = min(low[u], low[j]);
            if (dfn[u] < low[j]) {
                // bridge u - j
                is_bridge[i] = is_bridge[i ^ 1] = true;
            }
        } else if (i != (from ^ 1)) {
            low[u] = min(low[u], dfn[j]);
        }
    }

    if (dfn[u] == low[u]) {
        ++dcc_cnt;
        int y;
        do {
            y = stk[top--];
            id[y] = dcc_cnt;
        } while (y != u);
    }
}

int main() {
    fhj();
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m--) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    tarjan(1, -1);
    for (int i = 0; i < idx; ++i) {
        if (is_bridge[i]) {
            d[id[e[i]]]++;
        }
    }
    int cnt = 0;
    for (int i = 1; i <= dcc_cnt; ++i) {
        if (d[i] == 1) {
            cnt++;
        }
    }
    cout << (cnt + 1) / 2 << endl;
    return 0;
}