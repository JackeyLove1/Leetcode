#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <unordered_map>
#include <bitset>
#include <cstring>

using namespace std;

constexpr int N = 1e8 + 100, M = 18;

int n, m;
int nums[M];
int w[M];

bool dfs(int x, int num) {
    // x 奶牛号 num车厢数
    if (x == n) return true;
    for (int i = 1; i <= x + 1 && i <= num; ++i) {
        if (nums[x] + w[i] <= m) {
            w[i] = w[i] + nums[x];
            if (dfs(x + 1, num)) return true;
            w[i] = w[i] - nums[x];
        }

    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    for (int i = 1; i <= 18; ++i) {
        memset(w, 0, sizeof w);
        if (dfs(0, i)) {
            cout << i << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}