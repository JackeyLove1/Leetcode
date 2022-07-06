#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

using ll = long long;
using PII = pair<int, int>;

static constexpr int N = 1010 + 100, M = 20010 + 100;
int e[M], ne[M], w[M], h[N], idx;
int dist[N];
int n, m, k;
bool st[N];

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

inline bool check(int bound) {
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    deque<int> q;
    q.push_back(1);
    dist[1] = 0;
    while (!q.empty()) {
        auto t = q.front();
        q.pop_front();
        if (st[t]) continue;
        st[t] = true;
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i], x = static_cast<int>(w[i] > bound);
            if (dist[j] > dist[t] + x) {
                dist[j] = dist[t] + x;
                if (x) q.push_back(j);
                else q.push_front(j);
            }
        }
    }
    return dist[n] <= k;
}

int main() {
    fhj();
    memset(h, -1, sizeof h);
    cin >> n >> m >> k;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }
    int l = 0, r = 1e6 + 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    if (l == 1e6 + 1) cout << -1 << endl;
    else cout << l << endl;
    return 0;
}