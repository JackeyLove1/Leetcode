// practice 2022-11-12
// author: fanhj
#pragma GCC optimize(2)
#include <bits/stdc++.h>

using namespace std;

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

const int N = 100010, M = 300010;
int n, m;
int h[N], e[M], w[M], ne[M], idx;
using ll = long long;
ll dist[N];
int cnt[N];
bool st[N];

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}


bool spfa() {
    memset(dist, -0x3f, sizeof dist);
    queue<int>q;
    dist[n] = 0;
    st[n] = true;
    q.push(n);
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        st[t] = false;
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] < dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                if (cnt[j] >= n + 1) return false;
                if (!st[j]) {
                    st[j] = true;
                    q.push(j);
                }
            }
        }
    }
    return true;
}

int main() {
    fhj();
    memset(h, -1, sizeof h);
    cin >> n;
    string s;
    cin >> s;
    for(int i = 0; i < s.size(); ++i){
        if(s[i] == '>'){
            add(i + 1, i, 1);
        }else if (s[i] == '<'){
            add(i, i + 1, 1);
        }else {
            add(i, i + 1, 0), add(i + 1, i, 0);
        }
    }
    for(int i = 0; i < n; ++i) add(n, i, 1);
    if (!spfa()){
        cout << -1 << endl;
    }else {
        for(int i = 0; i < n; ++i){
            cout << dist[i] << " ";
        }
    }
    return 0;
}