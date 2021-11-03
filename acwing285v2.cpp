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
constexpr int N = 1e4 + 100;

int e[N], ne[N], h[N], idx;
int f[N][2];
int happy[N];
bool has[N];

inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

inline void init() {
    memset(h, -1, sizeof h);
    idx = 0;
}

int n;

void dfs(int u) {
    f[u][1] = happy[u];
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        dfs(j);
        f[u][0] += max(f[j][1], f[j][0]);
        f[u][1] += f[j][0];
    }
}

int main() {
    fhj();
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> happy[i];
    }
    int l, k;
    init();
    for (int i = 1; i < n; ++i) {
        cin >> l >> k;
        has[l] = true;
        add(k, l);
    }
    int root = 1;
    for (int i = 1; i <= n; ++i) {
        if (!has[i]) {
            root = i;
            break;
        }
    }
    dfs(root);
    cout << max(f[root][0], f[root][1]) << endl;
    return 0;
}