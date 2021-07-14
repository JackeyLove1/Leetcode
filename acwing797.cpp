// 差分模版

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

const int N = 1e6 + 100;
int n, m, t;

int d[N];

void insert(int l, int r, int c) {
    d[l] += c;
    d[r + 1] -= c;
}

int main() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> t;
        insert(i, i, t);
    }

    int l, r, c;
    while (m--) {
        cin >> l >> r >> c;
        insert(l, r, c);
    }

    for (int i = 1; i <= n; i++) {
        d[i] += d[i - 1];
        cout << d[i] << " ";
    }

    return 0;
}