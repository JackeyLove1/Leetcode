// 前缀和模版题

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

constexpr int N = 1e6 + 100;

int q[N], s[N];

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> q[i];
        s[i] = s[i - 1] + q[i];
    }

    while (m--) {
        int l, r;
        cin >> l >> r;
        cout << s[r] - s[l - 1] << endl;
    }

    return 0;
}