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

constexpr int N = 3e4 + 100;
ll f[N], w[N];

int main() {
    fhj();
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int sum = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> w[i];
            sum += w[i];
        }
        sort(w + 1, w + 1 + n);
        memset(f, 0, sizeof f);
        f[0] = 1;
        ll res = 0;
        for (int i = 1; i <= n; ++i) {
            res += f[w[i]];
            for (int j = sum; j >= w[i]; --j) {
                f[j] += f[j - w[i]];
            }
        }
        cout << res << endl;
    }
    return 0;
}