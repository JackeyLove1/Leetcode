#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

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

inline int cnt(int x) {
    return __builtin_popcount(x);
}

constexpr int N = 110;
int w[N];
int f[N][N];

int solve(int l, int r) {
    if (l > r) return 0;
    int &v = f[l][r];
    if (v != -1) return v;
    if (l == r) return v = w[l];
    v = max(v, solve(l, r - 1) + w[r]);
    v = max(v, solve(l + 1, r) + w[l]);
    for (int i = l + 1; i <= r; ++i) {
        v = max(v, solve(i + 1, r) + abs(w[i] - w[l]) * (i - l + 1));
    }
    for (int j = r - 1; j >= l; --j) {
        v = max(v, solve(l, j - 1) + abs(w[j] - w[r]) * (j - r + 1));
    }
    // cout << "l: " << l << " r: " << r << " v: " << v << endl;
    return v;
}

int main() {
    fhj();
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
    }
    memset(f, -1, sizeof f);
    int res = solve(1, n);
    cout << res << endl;
    return 0;
}