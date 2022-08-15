#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <unordered_set>


using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ull = unsigned long long;
using ll = long long;
using PII = pair<int, int>;
constexpr int N = 2000010, M = 2000010;

int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt, scc_size[N];

inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u, in_stk[u] = true;

    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        } else if (in_stk[j]) low[u] = min(low[u], dfn[j]);
    }
    if (dfn[u] == low[u]) {
        scc_cnt++;
        int y;
        do {
            y = stk[top--];
            in_stk[y] = false;
            id[y] = scc_cnt;
            scc_size[scc_cnt]++;
        } while (y != u);
    }
}


int main() {
    fhj();
    memset(h, -1, sizeof h), idx = 0;
    cin >> n >> m;
    int x, a, y, b;
    for (int i = 0; i < m; ++i) {
        cin >> x >> a >> y >> b;
        --x, --y;
        add(2 * x + !a, 2 * y + b);
        add(2 * y + !b, 2 * x + a);
    }
    for (int i = 0; i < 2 * n; ++i) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (id[2 * i] == id[2 * i + 1]) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }
    cout << "POSSIBLE" << endl;
    for (int i = 0; i < n; ++i) {
        if (id[2 * i] < id[2 * i + 1]) cout << "0 ";
        else cout << "1 ";
    }
    return 0;
}