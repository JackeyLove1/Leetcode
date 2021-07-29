#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <tuple>


using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for (auto &num : nums) cout << num << " ";
    cout << endl;
}

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for (auto &n : num) {
            cout << n << " ";
        }
        cout << endl;
    }
    cout << "ending ... " << endl;
}


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

constexpr int N = 1e6 + 100;

int h[N], e[N], ne[N], w[N], idx;
int d[N];
int n;
inline void init() {
    idx = 0;
    memset(h, -1, sizeof h);
}

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = b, ne[idx] = h[a], h[a] = idx++;
    d[b]++; // 入度
}

bool st[N];

void dfs(int u) {
    st[u] = true;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!st[j]){
            dfs(j);
        }
    }
}

void bfs(){
    queue<int> q;
    q.push(1);
    st[1] = true;
    while (q.size()){
        auto t = q.front();
        q.pop();
        for(int i = h[t]; i != -1; i = ne[i]){
            int j = e[i];
            if(!st[j]){
                st[j] = true;
                q.push(j);
            }
        }
    }
}

void topsort(){
    queue<int> q;
    for(int i = 1; i <= n; i++){
        if(!d[i]){
            q.push(i);
        }
    }

    while (q.size()){
        auto t = q.front();
        q.pop();
        for(int i = h[t]; i != -1; i = ne[i]){
            int j = e[i];
            if(--d[j] == 0){
                q.push(j);
            }
        }
    }
}

using PII = pair<int, int>; // distance, point
int dist[N];
inline int dijkstra(){
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    priority_queue<PII, vector<PII>, greater<>>heap;
    heap.push({0, 1});
    while (!heap.empty()){
        auto t = heap.top();
        heap.pop();

        int ver = t.second, distance = t.first;
        if(st[ver]) continue;
        st[ver] = true;

        for(int i = h[ver]; i != -1; i = ne[ver]){
            int j = e[i];
            if(dist[j] > distance + w[i]){
                dist[j] = distance + w[i];
                heap.push({dist[j], j});
            }
        }
    }

    if(dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}

int m;
struct Edge{
    int a, b, w;
}edges[N];

int bellman_ford(){
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            int a = edges[j].a, b = edges[j].b, w= edges[j].w;
            if(dist[b] > dist[a] + w){
                dist[b] = dist[a] + w;
            }
        }
    }

    if(dist[n] > 0x3f3f3f3f / 2) return 0;
    return dist[n];
}

int g[N][N];

inline void floyd(){
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                g[i][j] = min(g[i][k] + g[k][j], g[i][j]);
            }
        }
    }
}