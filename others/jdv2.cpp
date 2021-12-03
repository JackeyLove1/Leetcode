#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <bitset>
#include <cstring>
#include <queue>

using namespace std;
constexpr int N = 100;
int n, m, x, y, z;
// x move
// y turn around
// z put
char g[N][N];
using PII = pair<int, int>;
unordered_map<char, PII> cache;
using ll = long long;
const int debug = 0;

inline int calculate(int x1, int y1, int x2, int y2) {
    if (x1 == x2 && y1 == y2) {
        return z;
    }
    if (x1 == x2 && y1 != y2) {
        return int(abs(y1 - y2)) * x + z;
    }
    if (x1 != x2 && y1 == y2) {
        return int(abs(x1 - x2)) * x + z;
    }
    if (x1 != x2 && y1 != y2) {
        return y + z + int(abs(x1 - x2) + abs(y1 - y2)) * x;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> x >> y >> z;
    char ch;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> ch;
            cache[ch] = {i, j};
        }
    }
    ll res = 0;
    string s;
    cin >> s;
    int x0 = 1, y0 = 1;
    for (auto str : s) {
        PII t = cache[str];
        int x1 = t.first, y1 = t.second;
        res += calculate(x0, y0, x1, y1);
        if (debug) {
            cout << "res: " << res << " ";
            cout << "step: " << calculate(x0, y0, x1, y1) << endl;
        }
        x0 = x1, y0 = y1;
    }
    cout << res << endl;
    return 0;
}