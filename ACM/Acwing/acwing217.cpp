#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <numeric>

// #pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

const int N = 1e5 + 100, M = 2e5 + 100;
int e[M], ne[M], w[M], h[M], idx;
int dout[N];
double f[N];

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
    dout[a]++;
}

int n, m;

double dp(int u) { // 记忆化搜索
    if (f[u] >= 0) return f[u];
    f[u] = 0;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        f[u] += (w[i] + dp(j)) / dout[u];
    }
    return f[u];
}

int main() {
    fhj();
    cin >> n >> m;
    memset(h, -1, sizeof h);
    int a, b, c;
    while (m--) {
        cin >> a >> b >> c;
        add(a, b, c);
    }
    memset(f, -1, sizeof f);
    cout << dp(1) << endl;
    return 0;
}