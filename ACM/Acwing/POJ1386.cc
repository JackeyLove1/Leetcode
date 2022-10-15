#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <deque>
#include <functional>
#include <tuple>
#include <array>
#include <iomanip>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ll = long long;
using ull = unsigned long long;
using sll = __int128;
using PII = pair<int, int>;

using namespace std;

constexpr int N = 1e5 + 100, M = 1e5 + 5, INF = 0x3f3f3f3f;
int n, m;
int h[N], e[M], w[M], ne[M], cnt[M], dist[N], idx;
bool st[N];

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

void dijkstra(int s) {
    priority_queue<PII, vector<PII>, greater<>> q;
    memset(dist, 0x3f, sizeof dist);
    memset(st, false, sizeof st);
    dist[s] = 0;
    q.push({0, s});
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        if (st[u]) continue;
        st[u] = true;
        for (int i = h[u]; i != -1; i = ne[i]) {
            int v = e[i];
            if (dist[v] > dist[u] + w[i]) {
                dist[v] = dist[u] + w[i];
                q.push({dist[v], v});
            }
        }
    }
}

// SLF优化spfa
void spfa(int s) {
    memset(dist, 0x3f, sizeof dist);
    memset(st, false, sizeof st);
    deque<int> q;
    q.push_back(s), dist[s] = 0;
    while (!q.empty()) {
        auto t = q.front();
        st[t] = false;
        q.pop_front();
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                if (!st[j]) {
                    if (!q.empty() && dist[q.front()] > dist[j]) {
                        q.push_front(j);
                    } else {
                        q.push_back(j);
                    }
                    st[j] = true;
                }
            }
        }
    }
}

int p[N], rk[N];

int find(int x) {
    if (x != p[x]) return p[x] = find(p[x]);
    return x;
}

inline void merge(int a, int b) {
    int pa = find(a), pb = find(b);
    if (pa != pb) {
        if (rk[pa] < rk[pb]) {
            p[pa] = pb;
        } else {
            p[pb] = pa;
        }
    }
}

int in[N], out[N];

bool judge() {
    int cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < 26; ++i) {
        if (st[i]){
            if (in[i] == out[i]) continue;
            else if (in[i] == out[i] + 1) {
                if(++cnt1 > 1){
                    return false;
                }
            }
            else if (in[i] == out[i] - 1) {
                if (++cnt2 > 1){
                    return false;
                }
            }
            else return false;
        }
    }
    if (cnt1 + cnt2 == 1) return false;
    return true;
}

int main() {
    fhj();
    int T;
    cin >> T;
    while (T--) {
        memset(in, 0, sizeof in);
        memset(out, 0, sizeof out);
        memset(st, 0, sizeof st);
        for (int i = 0; i < 26; ++i) {
            p[i] = i;
        }
        cin >> n;
        char s[110];
        for (int i = 0; i < n; ++i) {
            scanf("%s", s);
            auto a = s[0] - 'a', b = s[strlen(s)-1] - 'a';
            ++in[a], ++out[b];
            st[a] = st[b] = true;
            merge(a, b);
        }
        int fs = 0;
        for (int i = 0; i < 26; ++i) {
            if (st[i] && find(i) == i) ++fs;
        }
        auto flag = (fs == 1) && judge();
        // cout << "fs == 1 is " << (fs == 1) << endl;
        // cout << "judge: " << judge() << endl;
        if (flag) {
            cout << "Ordering is possible." << endl;
        } else {
            cout << "The door cannot be opened." << endl;
        }
    }
    return 0;
}