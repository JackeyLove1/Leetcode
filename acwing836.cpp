#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

const int N = 1e6 + 100;

int p[N];

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

inline void merge(int a, int b) {
    p[find(a)] = find(b);
}


inline void query(int a, int b) {
    if (find(a) == find(b)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    ios::sync_with_stdio(false);
    for(int i = 1; i <= n; i++) p[i] = i;

    string op;
    int a, b;
    while (m--) {
        cin >> op >> a >> b;
        if (op == "M") {
            merge(a, b);
        } else {
            query(a, b);
        }
    }

    return 0;
}