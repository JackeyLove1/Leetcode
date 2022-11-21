#pragma GCC optimize(2)

#include <bits/stdc++.h>
using namespace std;

inline void fhj() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
}

constexpr int N = 20010, M = 350;

namespace suffix_auto {
int n, tot{1}, last{1};
string str;
struct Node {
  int len, fa;
  char ch[26];
} node[N];
int ans[N], now[N];
int e[N], ne[N], h[N], idx{0};
inline void extend(int c) {
  int p = last, np = last = ++tot;
  f[tot] = 1;
  node[np].len = node[p].len + 1;
  for (; p && !node[p].ch[c]; p = node[p].fa)
    node[p].ch[c] = np;
  if (!p)
    node[np].fa = 1;
  else {
    int q = node[p].ch[c];
    if (node[q].len == node[p].len + 1)
      node[np].fa = q;
    else {
      int nq = ++tot;
      node[nq] = node[q], node[nq].len = node[p].len + 1;
      node[q].fa = node[np].fa = nq;
      for (; p && node[p].ch[c] == q; p = node[p].fa)
        node[p].fa = nq;
    }
  }
}

void dfs(int u) {
  for (int i = h[u]; ~i; i = ne[i]) {
    int j = e[i];
    dfs(j);
    // do something
  }
}
} // namespace suffix_auto

namespace kmp {
char s[N], t[N];
int ne[N];
inline void kmp() {
  cin >> s + 1 >> t + 1;
  const int n = std::strlen(s + 1), m = std::strlen(t + 1);
  for (int i = 2, j = 0; i <= n; ++i) {
    while (j && s[i] != s[j + 1])
      j = ne[j];
    if (s[i] == s[j + 1])
      ++j;
    ne[i] = j;
  }
  for (int i = 2, j = 0; i <= m; ++j) {
    while (j && p[i] != s[j + 1])
      j = ne[j];
    if (p[i] == s[j + 1])
      ++j;
    if (j == n) {
      std::cout << i - n << std::endl;
      j = ne[j];
    }
  }
}
} // namespace kmp

namespace ac_auto {
char str[N];
int ch[N][26], cnt[N], ne[N], idx{0};
inline void insert(const char *s) {
  int p = 0;
  for (int i = 0; s[i]; ++i) {
    int j = s[i] - 'a';
    if (!ch[p][j])
      ch[p][j] = ++idx;
    p = ch[p][j];
  }
  ++cnt[idx];
}

inline void build() {
  std::queue<int> q;
  for (int i = 0, p = 0; i < 26; ++i) {
    if (ch[p][i])
      q.push(ch[p][i]);
  }
  while (!q.empty()) {
    auto u = q.front();
    q.pop();
    for (int i = 0; i < 26; ++i) {
      int v = ch[u][i];
      if (v)
        ne[v] = ch[ne[u]][i], q.push(v);
      else
        ch[v][i] = ch[ne[u]][i];
    }
  }
}

inline int query(const char *s) {
  int ans = 0;
  for (int i = 0, k = 0; s[i]; ++i) {
    k = ch[k][s[i] - 'a'];
    for (int j = k; j && ~cnt[j]; j = ne[j]) {
      ans += cnt[j], cnt[j] = -1;
    }
  }
  return ans;
}
inline void ac() {}
} // namespace ac_auto

namespace dijlstra {
constexpr int INF = 0x3f3f3f3f;
int dist[N], e[N], ne[N], w[N], h[N], idx{0};
bool st[N];
inline void init() { memset(h, -1, sizeof h); }
inline void add(int a, int b, int c) {
  e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

int dijkstra(int s) {
  memset(dist, 0x3f, sizeof dist);
  memset(st, false, sizeof st);
  using PII = pair<int, int>;
  std::priority_queue<PII, vector<PII>, greater<>> q;
  q.push({0, s}); // dist, ver
  dist[s] = 0;
  while (!q.empty()) {
    auto t = q.top();
    q.pop();
    int u = t.second;
    for (int i = h[u]; ~i; i = ne[i]) {
      int j = e[i];
      if (dist[j] > dist[u] + w[i]) {
        q.push({dist[j], j});
      }
    }
  }
  return dist[n];
}
} // namespace dijlstra

namespace spfa {
constexpr int INF = 0x3f3f3f3f;
int n, m;
int dist[N], e[N], ne[N], w[N], h[N], cnt[N], idx{0};
bool st[N];
inline void add(int a, int b, int c) {
  e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
inline void init() { memset(h, -1, sizeof h); }
int spfa(int s) {
  memset(dist, 0x3f, sizeof dist);
  memset(st, false, sizeof st);
  std::queue<int> q;
  q.push(s);
  dist[s] = 0, st[s] = true;
  while (!q.empty()) {
    auto t = q.front();
    q.pop();
    for (int i = h[t]; ~i; i = ne[i]) {
      int j = e[i];
      if (dist[j] > dist[t] + w[i]) {
        dist[j] = dist[t] + w[i];
        cnt[j] = cnt[t] + 1;
        if (cnt[j] >= n)
          return INF;
        if (!st[j]) {
          st[j] = true;
          q.push(j);
        }
      }
    }
  }
  return dist[n];
}
} // namespace spfa

namespace simple_block {
int n, m, len;
using ll = long long;
ll add[M], sum[M];
int w[N];
inline int get(int x) { return x / len; }
inline void change(int l, int r, int d) {
  if (get(l) == get(r)) {
    for (int i = l; i <= r; ++i)
      w[i] += d, sum[get(i)] += d;
  } else {
    int i = l, j = r;
    while (get(i) == get(l))
      w[i] += d, sum[get(i)] += d, ++i;
    while (get(j) == get(r))
      w[j] += d, sum[get(j)] += d, --j;
    for (int k = get(i); k <= get(j); ++k)
      sum[k] += d * len, add[k] += d;
  }
}
inline ll query(int l, int r) {
  ll res = 0;
  if (get(l) == get(r)) {
    for (int i = l; i <= r; ++i)
      res += w[i] + add[get(i)];
  } else {
    int i = l, j = r;
    while (get(i) == get(l))
      res += w[i] + add[get(i)], ++i;
    while (get(j) == get(r))
      res += w[j] + add[get(j)], --j;
    for (int k = get(i); k <= get(j); ++k)
      res += sum[k];
  }
  return res;
}

} // namespace block