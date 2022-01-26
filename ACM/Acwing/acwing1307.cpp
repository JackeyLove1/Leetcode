#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <cmath>
#include <cstdlib>

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

using ll = long long;
constexpr int mod = 5000011, N = 1e5 + 100;
int f[N];

int main() {
    fhj();
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= k + 1; i++) {
        f[i] = i + 1;
    }
    for (int i = k + 2; i <= n; i++) {
        f[i] = (f[i - 1] + f[i - k - 1]) % mod;
    }
    cout << f[n] << endl;
    return 0;
}