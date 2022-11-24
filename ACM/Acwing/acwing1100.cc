#include <bits/stdc++.h>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 1e6 + 100, INF = 1e9 + 100;
using ll = long long;
int n, m;
int dist[N];

int main() {
    fhj();
    cin >> n >> m;
    memset(dist, -1, sizeof dist);
    queue<int> q;
    q.push(n), dist[n] = 0;
    int step = 0;
    int up = m * 2 + 1;
    while (!q.empty()) {
        ++step;
        int sz = q.size();
        for (int i = 0; i < sz; ++i) {
            auto t = q.front();
            q.pop();
            if (t == m) {
                cout << dist[t] << endl;
                return 0;
            }
            if (t - 1 >= 0 && dist[t - 1] == -1) dist[t - 1] = step, q.push(t - 1);
            if (t + 1 <= up && dist[t + 1] == -1) dist[t + 1] = step, q.push(t + 1);
            if (t * 2 <= up && dist[t * 2] == -1) dist[t * 2] = step, q.push(t * 2);
        }
    }
    return 0;
}