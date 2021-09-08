#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <unordered_map>
#include <list>
#include <cmath>

using namespace std;

int ans = 0;
using PII = pair<int, int>;
map<PII, int> cache;

int dfs(int a, int b, int x, int y, int res) {
    PII p = {a, b};
    if (cache.count(p)) return cache[p];
    if (a < x || b < y) {
        return cache[p] = res;
    }
    int &v = cache[p];
    v = max(v, dfs(a - x, b - y, x, y, res + 1));
    v = max(v, dfs(a - y, b - x, x, y, res + 1));
    return v;
}

int main() {
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    ans = dfs(a, b, x, y, 0);
    cout << ans << endl;
    return 0;
}