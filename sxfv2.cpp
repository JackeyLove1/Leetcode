#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>

using namespace std;

int n;
constexpr int N = 110;
int nums[N];
int sum = 0;
int a, b, diff = 1e6;

void dfs(int cur, int v, int w) {
    // v 数量， w重量
    if (cur > n + 1 || v > n / 2 + 1) return;
    if (cur == n + 1 && v == n / 2) {
        if (abs(2 * w - sum) < diff) {
            a = min(w, sum - w);
            b = max(w, sum - w);
            diff = b - a;
        }
    }
    dfs(cur + 1, v + 1, w + nums[cur]);
    dfs(cur + 1, v, w);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> nums[i];
        sum += nums[i];
    }
    dfs(1, 0, 0);
    dfs(1, 1, nums[1]);
    cout << a << " " << b << endl;
    return 0;
}