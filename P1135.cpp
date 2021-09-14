#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <map>
#include <bitset>
#include <cstring>
#include <queue>

using namespace std;

constexpr int N = 300;
int nums[N], dist[N];
int n, a, b;

inline void bfs() {
    queue<int> q;
    q.push(a);
    dist[a] = 0;
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        if (t == b) return;
        int tmp = t + nums[t];
        if (tmp < 1 || tmp > n || dist[tmp] != -1) {
        } else {
            dist[tmp] = dist[t] + 1;
            q.push(tmp);
        }
        tmp = t - nums[t];
        if (tmp < 1 || tmp > n || dist[tmp] != -1) continue;
        dist[tmp] = dist[t] + 1;
        q.push(tmp);

    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> a >> b;
    for (int i = 1; i <= n; ++i) {
        cin >> nums[i];
    }
    memset(dist, -1, sizeof dist);
    bfs();
    cout << dist[b] << endl;
    return 0;
}