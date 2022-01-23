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

constexpr int N = 110;
using PII = pair<int, int>;

int n, m;
PII match[N][N];
bool g[N][N], st[N][N];
constexpr int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

/*
inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
*/
#define x first
#define y second

bool find(int x, int y) {
    for (int i = 0; i < 4; ++i) {
        int a = x + dx[i], b = y + dy[i];
        if (a > 0 && a <= n && b > 0 && b <= n && !st[a][b] && !g[a][b]) {
            st[a][b] = true;
            PII t = match[a][b];
            if (t.x == -1 || find(t.x, t.y)) {
                match[a][b] = {x, y};
                return true;
            }
        }
    }
    return false;
}

int main() {
    fhj();
    cin >> n >> m;
    while (m--) {
        int a, b;
        cin >> a >> b;
        g[a][b] = true;
    }
    int res = 0;
    memset(match, -1, sizeof match);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if ((i + j) % 2 == 0 && !g[i][j]) {
                memset(st, 0, sizeof st);
                if (find(i, j)) ++res;
            }
        }
    }
    cout << res << endl;
    return 0;
}