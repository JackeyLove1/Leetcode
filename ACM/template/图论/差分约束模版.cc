#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e5 + 100;
using ll = long long;
using PII = pair<int, int>;
int ne[N], h[N], e[N], w[N], cnt[N], idx;
bool st[N];
int dist[N];
int n, m;

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

bool spfa(int s) {
    memset(dist, 0x3f, sizeof dist);
    memset(st, false, sizeof st);
    memset(cnt, 0, sizeof cnt);
    priority_queue<PII> q;
    st[s] = true, dist[s] = 0;
    q.push({0, s});
    while (!q.empty()) {
        auto t = q.top().second;
        q.pop();
        st[t] = false;
        for (int i = h[t]; ~i; i = ne[i]) {
            auto j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                if (!st[j]) {
                    q.push({dist[j], j});
                    st[j] = true;
                    if (++cnt[j] >= n + 1) {// 包含超级源点
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    fhj();
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(b, a, c);
    }
    for (int i = 1; i <= n; ++i) {
        add(0, i, 0);
    }
    if (spfa(0)) {
        cout << "NO" << endl;
    } else {
        for (int i = 1; i <= n; ++i) {
            cout << dist[i] << " ";
        }
    }
    return 0;
}