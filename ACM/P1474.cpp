#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <climits>
#include <unordered_map>

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

using bll = __int128;
constexpr int N = 1e4 + 100;
int n, m, k;
int w[N];
ll f[N];

int main() {
    fhj();
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
    }
    f[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = w[i]; j <= m; ++j) {
            f[j] += f[j - w[i]];
        }
    }
    cout << f[m] << endl;
    return 0;
}