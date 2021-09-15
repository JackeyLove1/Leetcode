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
constexpr int N = 21;
int n;
string strs[N];
int g[N][N]; // i在前面，j在后面，重合的最小长度
int used[N];

const int debug = 0;

inline void pre(int i, int j) {
    // a在前，b在后
    g[i][j] = 0;
    string &a = strs[i];
    string &b = strs[j];
    int len = min(a.size(), b.size());
    int sz = a.size();
    for (int k = 1; k <= len; ++k) {
        if (a.substr(sz - k) == b.substr(0, k)) {
            g[i][j] = k;
            // if (debug) cout << "a.sub: " << a.substr(sz - i) << " b.sub: " << b.substr(0, i) << endl;
            if (debug) cout << "a: " << a << " b: " << b << " ";
            if (debug) cout << "len: " << k << endl;
            break;
        }
    }
}

inline void checkAll() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            pre(i, j);
        }
    }
}

static int res = 0;

void dfs(int k, int cur) {
    res = max(res, cur);
    ++used[k];
    for (int i = 1; i <= n; ++i) {
        if (g[k][i] > 0 && used[i] < 2) {
            dfs(i, cur + int(strs[i].size()) - g[k][i]);
        }
    }
    --used[k];
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> strs[i];
        // cout << strs[i] << endl;
    }
    char ch;
    cin >> ch;
    // cout << ch << endl;
    checkAll();
    for (int i = 1; i <= n; ++i) {
        if (strs[i][0] == ch) {
            dfs(i, int(strs[i].size()));
        }
    }
    cout << res << endl;
}