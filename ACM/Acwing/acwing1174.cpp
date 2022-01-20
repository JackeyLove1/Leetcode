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

constexpr int N = 10010, M = 50010;

int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
bool st[N];
int id[N], scc_cnt, Size[N];//每个强连通分的节点个数
int dout[N];
stack<int> stk;

inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;
    stk.push(u);
    st[u] = true;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        } else if (st[j]) {
            low[u] = min(low[u], dfn[j]);
        }
    }
    if (dfn[u] == low[u]) {
        // strong connection
        ++scc_cnt;
        int y;
        do {
            // 出栈直到并包括u
            // 他们都属于一个强连通分量
            y = stk.top();
            stk.pop();
            st[y] = false;
            id[y] = scc_cnt;
            Size[scc_cnt]++;
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
        add(a, b);
    }
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    // calculate dout
    for (int i = 1; i <= n; ++i) {
        for (int j = h[i]; j != -1; j = ne[j]) {
            int k = e[j];
            int a = id[i], b = id[k];
            if (a != b) dout[a]++; // 连通块a出度++
        }
    }
    int zeros = 0, sum = 0;
    for (int i = 1; i <= scc_cnt; ++i) {
        if (!dout[i]) {
            zeros++;
            sum += Size[i];
            if (zeros > 1) {
                sum = 0;
                break;
            }
        }
    }
    cout << sum << endl;
    return 0;
}


