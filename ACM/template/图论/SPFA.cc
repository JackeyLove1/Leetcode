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

constexpr int N = 1e5 + 100, M = 2e5 + 100, INF = 0x3f3f3f3f;
int n, m;
int h[N], w[M], e[M], ne[M], idx;
int dist[N], cnt[N];
bool st[N];

static inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

int spfa(int start, int times) {
    memset(dist, 0x3f, sizeof dist);
    dist[start] = 0;
    st[start] = true;
    queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int t = q.front();
        q.pop();
        st[t] = false;
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                if (!st[j]) {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
    return dist[n];
}

int main() {
    fhj();
    cin >> n >> m;
    memset(h, -1, sizeof h);

    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }

    int t = spfa(1, n);
    if (t == INF) cout << "impossible" << endl;
    else cout << t << endl;

    return 0;
}