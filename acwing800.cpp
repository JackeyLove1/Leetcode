// 数组目标和

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
    int n, m, x;
    unordered_map<int, int> um;
    cin >> n >> m >> x;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        um[a[i]] = i;
    }

    for (int i = 0; i < m; i++) {
        cin >> b[i];
        if (um.find(x - b[i]) != um.end()) {
            cout << um[x - b[i]] << " " << i << endl;
        }
    }

    return 0;
}