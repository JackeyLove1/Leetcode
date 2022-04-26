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
static constexpr int N = 1e6 + 100, M = 3100010;
using ll = long long;
using PII = pair<int, int>;
int n, m;

int h[N], w[N], e[N], ne[N], idx;
int dist[N];
bool st[N];

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

inline void init() {
    memset(h, -1, sizeof h);
    idx = 0;
}


inline int spfa() {
    memset(st, 0, sizeof st);
    memset(dist, 0x3f, sizeof dist);
    queue<int> q;
    q.push(1);
    dist[1] = 0;
    st[1] = true;
    while (!q.empty()) {
        auto ver = q.front();
        q.pop();
        st[ver] = false;
        for (int i = h[ver]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[ver] + w[i]) {
                dist[j] = dist[ver] + w[i];
                if (!st[j]) {
                    st[j] = true;
                    q.push(j);
                }
            }
        }
    }
    if (dist[n] >= INF / 2) return -1;
    return dist[n];
}

int main() {
    fhj();
    cin >> n >> m;
    init();
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }
    int ret = spfa();
    if (ret == -1) cout << "impossible" << endl;
    else cout << ret << endl;
    return 0;
}