// #pragma GCC optimize(2)
#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

int n, m;
constexpr int N = 2e4 + 100;
int e[N], ne[N], w[N], h[N], cnt[N], dist[N], idx{0};
bool st[N];

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

inline bool spfa(int u) {
    memset(st, false, sizeof st);
    memset(dist, 0x3f, sizeof dist);
    memset(cnt, 0, sizeof cnt);
    queue<int> q;
    q.push(u);
    st[u] = true, dist[u] = 0;
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        st[t] = false;
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                if (cnt[j] >= n) return false;
                if (!st[j]) {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
    return true;
}

int main() {
    fhj();
    int T;
    cin >> T;
    while (T--) {
        memset(h, -1, sizeof h);
        memset(e, 0, sizeof e);
        memset(ne, 0, sizeof ne);
        memset(w, 0, sizeof w);
        idx = 0;
        cin >> n >> m;
        int a, b, c;
        for (int i = 0; i < m; ++i) {
            cin >> a >> b >> c;
            add(a, b, c);
            if (c >= 0) add(b, a, c);
        }
        if (spfa(1)) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    }
    return 0;
}