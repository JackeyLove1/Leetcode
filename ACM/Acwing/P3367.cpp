#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <climits>
#include <functional>

using namespace std;
constexpr int N = 1e6 + 100;
int fa[N];
int n, m;

inline void init() {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
}

inline int find(int x) {
    if (x != fa[x]) {
        fa[x] = find(fa[x]);
    }
    return fa[x];
}

inline void merge(int a, int b) {
    int pa = find(a), pb = find(b);
    if (pa != pb) {
        fa[pb] = pa;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    init();
    int op, a, b;
    while (m--) {
        cin >> op >> a >> b;
        if (op == 1) {
            merge(a, b);
        } else {
            int pa = find(a), pb = find(b);
            if (pa == pb) cout << "Y" << endl;
            else cout << "N" << endl;
        }
    }
    return 0;
}