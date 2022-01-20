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

constexpr int N = 10010, M = N * 2;
using PII = pair<int, int>;
int n, m;
int h[N], e[M], w[M], ne[M], idx;
int dist[N];
int p[N];
int res[M];
int st[N];
vector<PII> query[N]; // first存查询的另外一个点，second存查询编号

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u, int fa) {
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        dist[j] = dist[u] + w[i];
        dfs(j, u);
    }
}

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

// 标记连通块算法
void tarjan(int u) {
    st[u] = 1;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!st[j]) {
            tarjan(j);
            p[j] = u; // tarjan递归标记根节点
        }
    }
    for (const auto &item : query[u]) {
        int y = item.first, id = item.second;
        if (st[y] == 2) {
            int father = find(y);
            res[id] = dist[u] + dist[y] - 2 * dist[father];
        }
    }
    st[u] = 2; // 以u为根节点标记完成
}

int main() {
    fhj();
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        if (a != b) {
            query[a].emplace_back(b, i);
            query[b].emplace_back(a, i);
        }
    }

    for (int i = 1; i <= n; i++) p[i] = i;

    dfs(1, -1);
    tarjan(1);

    for (int i = 0; i < m; i++) cout << res[i] << endl;

    return 0;

}