#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstring>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <cmath>

using namespace std;

constexpr int N = 1e6 + 100;

int n, m;
int h[N], cnt;

void down(int u) {
    int t = u;
    if (u * 2 <= cnt && h[u * 2] < h[t]) t = u * 2;
    if (u * 2 + 1 <= cnt && h[u * 2 + 1] < h[t]) t = u * 2 + 1;
    if (u != t) {
        swap(h[u], h[t]);
        down(t);
    }
}

void build() {
    cnt = n;
    for (int i = n / 2; i > 0; i--) {
        down(i);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    build();
    while (m--) {
        cout << h[1] << " ";
        h[1] = h[cnt--];
        down(1);
    }

    return 0;
}