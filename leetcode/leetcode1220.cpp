#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <atomic>
#include <thread>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

inline int count(int state) {
    return __builtin_popcount(state);
}

/*
constexpr int N = 1e4 + 100, INF = 0x3f3f3f3f;
int n, m;

int e[N], ne[N], h[N], w[N], idx;
int dist[N], st[N];
using PII = pair<int, int>;
unordered_set<int> farms;

inline void init() {
    memset(h, -1, sizeof h);
    idx = 0;
}

// 无向图
inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

int dijkstra(int source, int target) {
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    dist[source] = 0;
    priority_queue<PII, vector<PII>, greater<>> heap;
    heap.push({0, source}); // distance, ver
    while (!heap.empty()) {
        auto t = heap.top();
        heap.pop();
        int from = t.second;
        if (st[from]) continue;
        st[from] = true;
        for (int i = h[from]; i != -1; i = ne[i]) {
            int to = e[i];
            if (dist[to] > dist[from] + w[i]) {
                dist[to] = dist[from] + w[i];
                heap.push({dist[to], to});
            }
        }
    }
    if (dist[target] == INF) return -1;
    return dist[target];
}

*/
class Solution {
private:
    static constexpr int mod = 1e9 + 7;
    using ll = long long;
    vector<vector<int>> nums = {
            {1},
            {0, 2},
            {0, 1, 3, 4},
            {2, 4},
            {0}
    };
    ll f[20010][5];

    ll dfs(int pos, int pre) {
        if (pos == 0) return 1;
        ll &v = f[pos][pre];
        if (v != -1) return v;
        v = 0;
        for (auto &num : nums[pre]) {
            v = (v + dfs(pos - 1, num) % mod) % mod;
        }
        return v;
    }

public:
    int countVowelPermutation(int n) {
        // 计数dp
        ll res = 0;
        memset(f, -1, sizeof f);
        for (int i = 0; i < 5; ++i) {
            res = (res + dfs(n - 1, i) % mod) % mod;
        }
        return res;
    }
};

int main() {
    Solution s;
    cout << s.countVowelPermutation(1) << " res: 5" << endl;
    cout << s.countVowelPermutation(2) << " res: 10" << endl;
    cout << s.countVowelPermutation(5) << " res: 68" << endl;
    cout << s.countVowelPermutation(144) << " res: ?" << endl;
}