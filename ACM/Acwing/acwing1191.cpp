#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

constexpr int N = 1100;

int e[N], ne[N], h[N], idx;
int d[N];
int p[N];
int n;
int ans[N];

inline void init(){
    memset(h, -1, sizeof h);
}
inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    d[b]++;
}

inline int find(int x) {
    if (x != p[x]) return p[x] = find(x);
    return x;
}

inline void merge(int a, int b) {
    p[find(a)] = find(b);
}

inline void topsort() {
    queue<int> q;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (!d[i])q.push(i);
    }
    while (!q.empty()) {
        auto t = q.front();
        ans[++cnt] = t;
        q.pop();
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (--d[j] == 0) q.push(j);
        }
    }
    // if(cnt != n) cout << "wrong ";
    for(int i = 1; i <= n; i++) cout << ans[i] <<" ";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    init();
    for (int i = 1; i <= n; i++) {
        int x;
        while (cin >> x, x) {
            add(i, x);
        }
    }
    topsort();
    return 0;
}