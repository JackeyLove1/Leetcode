#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>

using namespace std;

constexpr int MOD = 80112002, N = 1e4 + 100;
int n, m;

int h[N], e[N], ne[N], idx;
int in[N], out[N]; // 入度，出度
int f[N]; // 计数，到达该点的最大路径数目

// 添加一条边a->b
inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    ++out[a], ++in[b];
}

// 初始化
inline void init() {
    idx = 0;
    memset(h, -1, sizeof h);
    // memset(in, 0, sizeof in);
    // memset(out, 0, sizeof out);
    // memset(e, 0, sizeof e);
    // memset(f, 0, sizeof f);
    // memset(ne, 0, sizeof ne);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    int a, b;
    init();
    while (m--) {
        cin >> a >> b;
        add(a, b);
    }
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (in[i] == 0) {
            f[i] = 1;
            q.push(i);
        }
    }
    int res = 0;
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            f[j] = (f[t] + f[j]) % MOD;
            if (--in[j] == 0) {
                if (out[j] == 0) {
                    res = (res + f[j]) % MOD;
                } else {
                    q.push(j);
                }
            }
        }
    }
    cout << res << endl;
    return 0;
}

