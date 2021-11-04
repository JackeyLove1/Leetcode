#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
// #include <map>
#include <bitset>
#include <queue>
#include <deque>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

using ll = long long;
constexpr int N = 1000;

int e[N], ne[N], h[N], idx;
int f[N][N];
int w[N];

inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

inline void init() {
    memset(h, -1, sizeof h);
    idx = 0;
}

int n, m;

void dfs(int u) {
    for (int i = h[u]; i != -1; i = ne[i]) {
        int to = e[i];
        dfs(to);
        for (int j = m + 1; j >= 1; j--) {
            for (int k = 0; k < j; k++) {
                f[u][j] = max(f[u][j], f[to][k] + f[u][j - k]);
            }
        }
    }
}

int main() {
    fhj();
    cin >> n >> m;
    int k, s;
    init();
    for (int i = 1; i <= n; ++i) {
        cin >> k >> s;
        add(k, i);
        f[i][1] = s;
    }
    dfs(0);
    cout << f[0][m + 1] << endl;
    return 0;
}