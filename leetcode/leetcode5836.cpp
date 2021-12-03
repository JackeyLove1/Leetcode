#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <bitset>
#include <cstring>
#include <string>

using namespace std;

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for_each(num.begin(), num.end(), [](const T &t) { cout << t << " "; });
        cout << endl;
    }
}

template<typename T>
inline void print(vector<T> &num) {
    for_each(num.begin(), num.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    static constexpr int N = 1e6 + 100, M = 220, MOD = 1e9 + 7;
    using ll = long long;
    int e[N], w[N], ne[N], h[N], idx;
    int st[N];
    ll dist[N];
    // int g[M][M];

    void init() {
        memset(dist, 0x3f, sizeof dist);
        memset(h, -1, sizeof h);
    }

    void add(int a, int b, int c) {
        e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
    }

    void dijkstra(int n) {
        using PII = pair<int, int>;
        priority_queue<PII, vector<PII>, greater<>> heap;
        heap.push({0, 0}); // dis, ver
        dist[0] = 0;
        while (!heap.empty()) {
            auto[dis, ver] = heap.top();
            dis = ll(dis);
            heap.pop();
            if (st[ver]) continue;
            st[ver] = true;
            for (int i = h[ver]; i != -1; i = ne[i]) {
                int j = e[i];
                if (dist[j] > dis + w[i]) {
                    dist[j] = dis + w[i];
                    heap.emplace(dist[j], j);
                }
            }
        }
    }

    int countPaths(int n, vector<vector<int>> &roads) {
        init();
        for (auto &&road: roads) {
            add(road[0], road[1], road[2]);
            add(road[1], road[0], road[2]);
        }
        dijkstra(n);
        vector<vector<int>> g(n + 1);
        for (auto &&road : roads) {
            int x = road[0], y = road[1], z = road[2];
            if (dist[x] - dist[y] == z) {
                g[y].push_back(x);
            }
            if (dist[y] - dist[x] == z) {
                g[x].push_back(y);
            }
        }

        vector<int> f(M, -1);
        function<int(int)> dfs = [&](int x) -> int {
            if (x == n - 1)return 1;
            if (f[x] != -1) return f[x];
            f[x] = 0;
            for (auto &y : g[x]) {
                f[x] = (f[x] + dfs(y)) % MOD;
            }
            return f[x];
        };

        return dfs(0);
    }
};