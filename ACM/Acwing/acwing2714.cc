#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <memory>

using namespace std;

static inline int read() {
    int x = 0, f = 0, ch;
    while (!isdigit(ch = getchar())) f |= ch == '-';
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
}

using ull = unsigned long long;
using LL = long long;
using PII = pair<int, int>;

constexpr int N = 200010;

int n;
int v[N], dist[N], l[N], r[N], idx;
int p[N];

inline bool cmp(int x, int y) {
    return v[x] != v[y] ? v[x] < v[y] : x < y;
}

int find(int x) {
    if (p[x] != x) return p[x] = find(p[x]);
    return x;
}

int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (cmp(y, x)) swap(x, y);
    r[x] = merge(r[x], y);
    if (dist[r[x]] > dist[l[x]]) swap(l[x], r[x]);
    dist[x] = dist[r[x]] + 1;
    return x;
}

int main() {
    fhj();
    cin >> n;
    v[0] = 2e9;
    while (n--) {
        int t, x, y;
        cin >> t;
        if (t == 1) {
            cin >> x;
            v[++idx] = x;
            dist[idx] = 1;
            p[idx] = idx;
        } else if (t == 2) {
            cin >> x >> y;
            x = find(x), y = find(y);
            if (x != y) {
                if (cmp(y, x)) swap(x, y);
                p[y] = x;
                merge(x, y);
            }
        } else if (t == 3) {
            cin >> x;
            cout << v[find(x)] << endl;
        } else {
            cin >> x;
            x = find(x);
            if (cmp(r[x], l[x])) swap(l[x], r[x]);
            p[x] = l[x], p[l[x]] = l[x];
            merge(l[x], r[x]);
        }
    }
    return 0;
}