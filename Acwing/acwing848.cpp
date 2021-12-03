#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <cstring>

using namespace std;

// 拓扑排序模版题

const int N = 1e5 + 100;

int n, m;
int h[N], e[N], ne[N], idx;
int d[N];
int res[N];

inline void init() {
    memset(h, -1, sizeof h);
}

inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

bool topSort() {
    queue<int> q;
    int cnt = 0;
    for(int i = 1; i <= n; i++){
        if(!d[i]){
            q.push(i);
            // res[cnt++] = i;
        }
    }
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        res[cnt++] = t;
        // cout << t << " ";
        // cout << "cnt: "<<cnt << endl;

        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (--d[j] == 0) {
                q.push(j);
            }
        }
    }
    return cnt == n ;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    int x, y;
    init();
    while (m--) {
        cin >> x >> y;
        add(x, y);
        d[y]++;
    }
    if (topSort()) {
        for (int i = 0; i < n; i++) cout << res[i] << " ";
    } else {
        cout << -1 << endl;
    }
    return 0;
}