#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <map>
#include <bitset>
#include <cstring>
#include <queue>

using namespace std;

constexpr int N = 15, M = 300;
int col[M], row[M], diag1[M], diag2[M];
int n;
static int res = 0;

void print() {
    if (++res <= 3) {
        for (int i = 1; i <= n; ++i) {
            cout << col[i] << " ";
        }
        cout << endl;
    }
}

void dfs(int x) { // 第x行
    if (x == n + 1) {
        print();
        return;
    }
    for (int y = 1; y <= n; ++y) {
        // 第y列
        if (row[y] || diag1[x - y + n] || diag2[x + y]) continue;
        col[x] = y;
        row[y] = 1;
        diag1[x - y + n] = 1;
        diag2[x + y] = 1;
        dfs(x + 1);
        row[y] = 0;
        diag1[x - y + n] = 0;
        diag2[x + y] = 0;
    }
}

int main() {
    cin >> n;
    dfs(1);
    cout << res << endl;
    return 0;
}