#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <cstring>

using namespace std;

const int N = 1e5 + 10;

int n, m;
int e[N], w[N], h[N], ne[N], idx;
int dist[N], cnt[N];
bool st[N];

inline void init() {
    memset(h, -1, sizeof h);
    memset(dist, 0x3f, sizeof dist);
}

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

int spfa() {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        st[1] = true;
        q.push(i);
    }

    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        st[t] = false;

        for (int i = h[t]; i != -1; i = ne[i]) {
            auto j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                if (cnt[j] >= n) return true;
                if (!st[j]) {
                    st[j] = true;
                    q.push(j);
                }
            }
        }
    }
    return false;
}

int main() {
    cin >> n >> m;
    init();
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }
    if (spfa()) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}