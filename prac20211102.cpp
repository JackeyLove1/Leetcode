#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>
#include <bitset>
#include <queue>
#include <deque>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

constexpr int N = 1e6 + 100;
using ll = long long;

int h[N], ne[N], e[N], w[N], match[N], idx;
bool st[N];
int n1, n2, m;

inline void init() {
    memset(h, -1, sizeof h);
    idx = 0;
}

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

bool find(int x) {
    for (int i = h[x]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!st[j]) {
            st[j] = true;
            if (!match[j] || find(j)) {
                match[j] = x;
                return true;
            }
        }
    }
    return false;
}

void dfs(int u) {
    st[u] = true;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!st[j]) {
            // process
            dfs(j);
        }
    }
}

void bfs(int u) {
    queue<int> q;
    q.push(u);
    st[u] = true;
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (!st[j]) {
                st[j] = true;
                q.push(j);
            }
        }
    }
}

int dist[N];
using PII = pair<int, int>;
int n;

int dijkstra() {
    memset(dist, 0x3f, sizeof dist);
    priority_queue<PII, vector<PII>, greater<>> heap;
    heap.push({0, 1}); // dis, ver
    dist[1] = 0;
    while (!heap.empty()) {
        auto t = heap.top();
        heap.pop();
        auto dis = t.first, ver = t.second;
        if (st[ver]) continue;
        st[ver] = true;
        for (int i = h[ver]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[ver] + w[i]) {
                dist[j] = dist[ver] + w[i];
                heap.push({dist[j], j});
            }
        }
    }
    if (dist[n] == 0x3f3f3f3f) return -1;
    else return dist[n];
}

int d[N][N];

inline void floyed() {
    for (int i = 1; i <= n; ++i) d[i][i] = 0;
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; ++j) {
                d[i][j] = min(d[i][k] + d[k][j], d[i][j]);
            }
        }
    }
}

