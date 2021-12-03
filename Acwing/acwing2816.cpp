// 判断是否为子序列

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_map>

using namespace std;

const int N = 1e5 + 100;

int a[N], b[N];

int main() {
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (a[i] == b[j]) i++, j++;
        else j++;
    }
    if (i == n) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}