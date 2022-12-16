#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
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

constexpr int N = 1e5 + 100, INF = 0x3f3f3f3f;
int n, m;

int e[N], ne[N], h[N], w[N], idx;
int dist[N], st[N];
using PII = pair<int, int>;

inline void init() {
    memset(h, -1, sizeof h);
    idx = 0;
}

// 无向图
inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

int dijkstra(int source, int target) {
    memset(st, 0, sizeof st);
    memset(dist, 0x3f, sizeof dist);
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

int main() {
    fhj();
    int from, to;
    cin >> n >> m >> from >> to;
    int rs, re, ci;
    init();
    for (int i = 0; i < m; ++i) {
        cin >> rs >> re >> ci;
        add(rs, re, ci);
        add(re, rs, ci);
    }
    int res = dijkstra(from, to);
    cout << res << endl;
    return 0;
}

/*
#include<bits/stdc++.h>

const int MaxN = 100010, MaxM = 500010;

struct edge
{
    int to, dis, next;
};

edge e[MaxM];
int head[MaxN], dis[MaxN], cnt;
bool vis[MaxN];
int n, m, s;

inline void add_edge( int u, int v, int d )
{
    cnt++;
    e[cnt].dis = d;
    e[cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}

struct node
{
    int dis;
    int pos;
    bool operator <( const node &x )const
    {
        return x.dis < dis;
    }
};

std::priority_queue<node> q;

inline void dijkstra()
{
    dis[s] = 0;
    q.push( ( node ){0, s} );
    while( !q.empty() )
    {
        node tmp = q.top();
        q.pop();
        int x = tmp.pos, d = tmp.dis;
        if( vis[x] )
            continue;
        vis[x] = 1;
        for( int i = head[x]; i; i = e[i].next )
        {
            int y = e[i].to;
            if( dis[y] > dis[x] + e[i].dis )
            {
                dis[y] = dis[x] + e[i].dis;
                if( !vis[y] )
                {
                    q.push( ( node ){dis[y], y} );
                }
            }
        }
    }
}

int main()
{
    scanf( "%d%d%d", &n, &m, &s );
    for(int i = 1; i <= n; ++i)dis[i] = 0x7fffffff;
    for( register int i = 0; i < m; ++i )
    {
        register int u, v, d;
        scanf( "%d%d%d", &u, &v, &d );
        add_edge( u, v, d );
    }
    dijkstra();
    for( int i = 1; i <= n; i++ )
        printf( "%d ", dis[i] );
    return 0;
}
*/