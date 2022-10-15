#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <deque>
#include <functional>
#include <tuple>
#include <array>
#include <iomanip>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ll = long long;
using ull = unsigned long long;
using sll = __int128;
using PII = pair<int, int>;

using namespace std;

constexpr int N = 1e6 + 100, M = 1e6 + 5, INF = 0x3f3f3f3f;
int n, m;
int h[N], e[M], w[M], ne[M], cnt[M], dist[N], idx;
bool st[N];

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

void dijkstra(int s) {
    priority_queue<PII, vector<PII>, greater<>> q;
    memset(dist, 0x3f, sizeof dist);
    memset(st, false, sizeof st);
    dist[s] = 0;
    q.push({0, s});
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        if (st[u]) continue;
        st[u] = true;
        for (int i = h[u]; i != -1; i = ne[i]) {
            int v = e[i];
            if (dist[v] > dist[u] + w[i]) {
                dist[v] = dist[u] + w[i];
                q.push({dist[v], v});
            }
        }
    }
}

// SLF优化spfa
void spfa(int s) {
    memset(dist, 0x3f, sizeof dist);
    memset(st, false, sizeof st);
    deque<int> q;
    q.push_back(s), dist[s] = 0;
    while (!q.empty()) {
        auto t = q.front();
        st[t] = false;
        q.pop_front();
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                if (!st[j]) {
                    if (!q.empty() && dist[q.front()] > dist[j]) {
                        q.push_front(j);
                    } else {
                        q.push_back(j);
                    }
                    st[j] = true;
                }
            }
        }
    }
}

int main() {
    fhj();
    int t, r, p, s;
    cin >> t >> r >> p >> s;
    memset(h, -1, sizeof h);
    int a, b, c;
    for (int i = 1; i <= r; i++) {
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    for (int i = 1; i <= p; i++) {
        cin >> a >> b >> c;
        add(a, b, c);
    }
    spfa(s);
    for (int i = 1; i <= t; i++) {
        if (dist[i] == INF) {
            cout << "NO PATH" << endl;
        } else {
            cout << dist[i] << endl;
        }
    }
    return 0;
}