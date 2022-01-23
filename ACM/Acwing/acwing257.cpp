#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stack>


#pragma GCC optimize(2)

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

inline int count(int state) {
    return __builtin_popcount(state);
}

constexpr int N = 20010, M = 200010;

int n, m;
int h[N], e[M], w[M], ne[M], idx;
int color[N];

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

bool dfs(int u, int c, int limit) {
    color[u] = c;
    for (int i = h[u]; i != -1; i = ne[i]) {
        if (w[i] <= limit) continue;
        int j = e[i];
        if (color[j]) {
            if (color[j] == c) return false;
        } else if (!dfs(j, 3 - c, limit)) return false;
    }
    return true;
}

bool check(int limit) {
    memset(color, 0, sizeof color);
    for (int i = 1; i <= n; ++i) {
        if (!color[i]) {
            if (!dfs(i, 1, limit)) return false;
        }
    }
    return true;
}

int main() {
    fhj();
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    int l = 0, r = 1e8;
    while (l < r){
        int mid = l + r >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l << endl;
    return 0;
}