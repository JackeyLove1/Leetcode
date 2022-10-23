#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e6 + 100;
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
                    if (++cnt[j] > n + 1) {
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
    int s = n + 1;
    for (int i = 0; i <= n; ++i) add(s, i, 0);
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(b, a - 1, -c);
    }
    for (int i = 1; i <= n; ++i) {
        add(i - 1, i, 1);
        add(i, i - 1, 0);
    }
    spfa(s);
    auto minn = INT32_MAX;
    for(int i = 0; i <= n; ++i){
        minn = std::min(minn, dist[i]);
    }
    cout << dist[n] - minn << endl;
    return 0;
}