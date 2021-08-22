#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <cstring>

using namespace std;

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for_each(num.begin(), num.end(), [](const T &t) { cout << t << " "; });
        cout << endl;
    }
}


class Solution {
public:
    const int debug = 0;
    static constexpr int N = 13, INF = 0x3f3f3f3f;
    int g[N][N];
    // int dist[N][N];

    void init() {
        memset(g, 0x3f, sizeof g);
        for (int i = 0; i < N; i++) g[i][i] = 0;
    }

    void add(int a, int b) {
        g[a][b] = g[b][a] = 1;
    }

    int shortestPathLength(vector<vector<int>> &graph) {
        int n = graph.size();
        init();
        for (int a = 0; a < graph.size(); a++) {
            for (auto &b : graph[a]) {
                add(a, b);
            }
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
                }
            }
        }
        if (debug) {
            cout << "g: " << endl;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cout << g[i][j] << " ";
                }
                cout << endl;
            }
        };
        vector<vector<int>> f(1 << n, vector<int>(n, INF));
        f[0][0] = 0, f[1][0] = 0;
        for (int i = 0; i < n; i++) f[1 << i][i] = 0;
        for (int i = 0; i < 1 << n; i++) {
            for (int j = 0; j < n; j++) {
                if (i & (1 << j)) {
                    for (int k = 0; k < n; k++) {
                        if ((i - (1 << j)) >> k & 1) {
                            f[i][j] = min(f[i][j], f[i - (1 << j)][k] + g[k][j]);
                        }
                    }
                }
            }
        }
        int res = INF;
        for (int i = 0; i < n; i++) res = min(res, f[(1 << n) - 1][i]);
        return res;
    }
};

int main() {
    auto s = Solution();
    vector<vector<int>> nums = {{1, 2, 3},
                                {0},
                                {0},
                                {0}};
    cout << s.shortestPathLength(nums) << " res: 4" << endl;
    return 0;
}