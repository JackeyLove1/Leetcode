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

constexpr int N = 1e5 + 10, M = 2e5 + 10;
int e[M], ne[M], h[N], idx;
int st[N];
int n, m;

inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

bool dfs(int u, int color) {
    st[u] = color;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!st[j]) {
            if (!dfs(j, 3 - color)) return false;
        } else if (st[j] == color) return false;
    }
    return true;
}

int main() {
    fhj();
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    bool flag = true;
    for (int i = 1; i <= n; ++i) {
        if (!st[i]) {
            if (!dfs(i, 1)) {
                flag = false;
                break;
            }
        }
    }
    if (flag) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;

}