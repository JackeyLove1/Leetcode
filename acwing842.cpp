// 排列模版题

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <unordered_set>

using namespace std;

const int N = 10;
int st[N], path[N];
int n;

void dfs(int u) {
    if (u == n) {
        for (int i = 0; i < n; i++) {
            cout << path[i] << " ";
        }
        cout << endl;
    }

    for (int i = 1; i <= n; i++) {
        if (!st[i]) {
            st[i] = true;
            path[u] = i;
            dfs(u + 1);
            st[i] = false;
        }
    }
}

int main() {
    cin >> n;
    dfs(0);
}