#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <cstring>
#include <cmath>
#include <list>
#include <atomic>
#include <cstring>
#include <cstdlib>

using namespace std;

template<typename T>
static inline void print(vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class TreeNode {
public:
    int val;
    TreeNode *right, *left;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int val_) : val(val_), left(nullptr), right(nullptr) {}

};

// build a list
static constexpr int N = 1e6 + 100;

int h[N], e[N], w[N], ne[N], idx;

static inline void init() {
    memset(h, -1, sizeof h);
    idx = 0;
}

// add a edge from a to b , weight is c
static inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}


// flag array
bool st[N];

// dfs
void dfs(int u) {
    st[u] = true;
    // i is idx
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!st[j]) dfs(j);
    }
}

// bfs
void bfs(int u) {
    queue<int> q;
    st[u] = true;
    q.push(u);
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (st[j]) continue;
            st[j] = true;
            q.push(j);
        }
    }
}

// topsort
int n;
int d[N], top[N];

bool topsort() {
    int cnt = 0;
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (!d[i]) {
            q.push(i);
            top[cnt++] = i;
        }
    }
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (--d[j] == 0) {
                q.push(j);
                top[cnt++] = j;
            }
        }
    }
    return cnt == n;
}

// dijkstra
static constexpr int INF = 0x3f3f3f3f;
int dist[N]; // distant array
int djkstra() {
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    using PII = pair<int, int>;
    priority_queue<PII, vector<PII>, greater<>> heap;
    heap.push({0, 1}); // distance, point
    while (!heap.empty()) {
        auto t = heap.top();
        heap.pop();
        int ver = t.second, dis = t.first;
        if (st[ver]) continue;
        st[ver] = true;
        for (int i = h[ver]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dis + w[i]) {
                dist[j] = dis + w[i];
                heap.push({dist[j], j});
            }
        }
    }
    if (dist[n] == INF) return INF;
    return dist[n];
}

// floyed
int g[N][N];

void floyed() {
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
}

//

class Solution {
public:
    int numFriendRequests(vector<int> &ages) {
        int res = 0;
        unordered_map<int, int> m;
        for (const int age : ages) {
            ++m[age];
        }
        sort(ages.begin(), ages.end());
        ages.erase(unique(ages.begin(), ages.end()), ages.end());
        print(ages);
        for (int i = 0; i < ages.size(); ++i) {
            for (int j = 0; j < ages.size(); ++j) {
                if (ages[j] <= ages[i] * 0.5 + 7) continue;
                if (ages[j] > ages[i]) continue;
                if (ages[j] > 100 && ages[i] < 100) continue;
                if (i == j && m[ages[i]] > 1)res += m[ages[i]] * (m[ages[i]] - 1);
                if (i != j) res += m[ages[i]] * m[ages[j]];
            }
        }
        return res;
    }
};

class Solution2 {
public:
    int numFriendRequests(vector<int> &ages) {
        int res = 0;
        for (int i = 0; i < ages.size(); ++i) {
            for (int j = 0; j < ages.size(); ++j) {
                if (ages[j] <= ages[i] * 0.5 + 7) continue;
                if (ages[j] > ages[i]) continue;
                if (ages[j] > 100 && ages[i] < 100) continue;
                ++res;
            }
        }
        return res;
    }
};

int main() {
    vector<int> nums = {98, 60, 24, 89, 84, 51, 61, 96, 108, 87, 68, 29, 14, 11, 13, 50, 13, 104, 57, 8, 57, 111, 92,
                        87, 9, 59, 65, 116, 56, 39, 55, 11, 21, 105, 57, 36, 48, 93, 20, 94, 35, 68, 64, 41, 37, 11, 50,
                        47, 8, 9};

    Solution s;
    cout << s.numFriendRequests(nums) << " res: 439" << endl;
    Solution2 s2;
    cout << s2.numFriendRequests(nums) << " res: 439" << endl;
}