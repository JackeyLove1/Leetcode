// 连通块的个数

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

const int N = 1e6 + 100;

int p[N], cnt[N];

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

inline void merge(int a, int b) {
    // p[find(a)] = find(b);
    int fa = p[find(a)], fb = p[find(b)];
    if (fa != fb) {
        p[fa] = fb;
        cnt[fb] += cnt[fa];
    }
}


inline void query(int a, int b) {
    if (find(a) == find(b)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}

inline int query(int a) {
    cout << cnt[find(a)] << endl;
}

int main() {
    int n, m;
    cin >> n >> m;
    ios::sync_with_stdio(false);
    for (int i = 1; i <= n; i++) p[i] = i, cnt[i] = 1;

    string op;
    int a, b;
    while (m--) {
        cin >> op >> a;
        if (op == "C") {
            cin >> b;
            merge(a, b);
        } else if (op == "Q1") {
            cin >> b;
            query(a, b);
        } else {
            query(a);
        }
    }

    return 0;
}