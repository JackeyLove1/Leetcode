#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <unordered_map>
#include <unordered_set>


using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;

constexpr int N = 1e4 + 100, M = 1e5 + 100, INF = 0x3f3f3f3f;
int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt, Size[N];
int dout[N];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

inline void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u, in_stk[u] = true;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        } else if (in_stk[j]) low[u] = min(low[u], dfn[j]);
    }

    if (dfn[u] == low[u]) {
        ++scc_cnt;
        int y;
        do {
            y = stk[top--];
            in_stk[y] = false;
            id[y] = scc_cnt;
            Size[scc_cnt]++;
        } while (y != u);
    }
}


int main() {
    fhj();
    cin >> n >> m;
    int a, b;
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        add(a, b);
    }
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = h[i]; ~j; j = ne[j]) {
            int k = e[j];
            a = id[i], b = id[k];
            if (a != b) {
                dout[a]++;
            }
        }
    }
    int res = 0, zero = 0;
    for (auto i = 1; i <= scc_cnt; ++i) {
        if (dout[i] == 0) {
            zero++;
            res += Size[i];
            if (zero > 1) {
                res = 0;
                break;
            }
        }
    }
    cout << res << endl;
    return 0;
}
