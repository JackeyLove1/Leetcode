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

constexpr int N = 1100, MOD = 1e9 + 7, INF = 1e6 + 100;
string s;
int f[N][N];

int solve(int l, int r) {
    int &v = f[l][r];
    if (v != -1) return v;
    if (l > r) return v = INF;
    if (l == r) return v = 0;
    if (l + 1 == r && s[l] == s[r]) return v = 0;
    if (l + 1 == r && s[l] != s[r]) return v = 1;
    v = min(solve(l + 1, r), solve(l, r - 1)) + 1;
    if (s[l] == s[r]) {
        v = min(v, solve(l + 1, r - 1));
    } else {
        v = min(v, solve(l + 1, r - 1) + 2);
    }
    return v;
}

int main() {
    fhj();
    cin >> s;
    memset(f, -1, sizeof f);
    cout << solve(0, s.size() - 1) << endl;
    return 0;
}