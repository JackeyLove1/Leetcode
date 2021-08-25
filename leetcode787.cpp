class Solution {
public:
    static constexpr int N = 200, INF = 0x3f3f3f3f, M = 1e4 + 100;
    const int debug = 0;
    struct Edge {
        int a, b, c;
    } e[M];
    int dist[N], last[N];

    int bellman_ford(int src, int dst, int m, int k) {
        memset(dist, 0x3f, sizeof dist);
        dist[src] = 0;
        for (int i = 0; i < k; i++) {
            memcpy(last, dist, sizeof dist);
            if (debug) cout << "i: " << i << endl;
            for (int j = 0; j < m; j++) {
                auto a = e[j].a, b = e[j].b, c = e[j].c;
                dist[b] = min(dist[b], last[a] + c);
                if (debug) cout << "a: " << a << " b: " << b << " dist: " << dist[b] << endl;
            }
        }
        if (dist[dst] > INF / 2) return -1;
        return dist[dst];
    }

    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k) {
        for (int i = 0; i < flights.size(); i++) {
            auto flight = flights[i];
            e[i] = {flight[0], flight[1], flight[2]};
        }

        return bellman_ford(src, dst, flights.size(), k + 1);
    }
};
