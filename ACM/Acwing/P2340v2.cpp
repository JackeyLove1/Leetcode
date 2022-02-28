#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <numeric>

// #pragma GCC optimize(2)

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

constexpr int N = 405, M = 4e5;
using PII = pair<int, int>;
PII cow[N];
int f[2 * M + 10];
int n, m;

int main() {
    fhj();
    cin >> n;
    memset(f, -0x3f, sizeof f);
    for (int i = 1; i <= n; ++i) {
        cin >> cow[i].first >> cow[i].second;
    }
    f[M] = 0;
    for (int i = 1; i <= n; ++i) {
        if (cow[i].second >= 0) {
            for (int j = 2 * M; j >= cow[i].second; --j) {
                f[j] = max(f[j], f[j - cow[i].second] + cow[i].first);
            }
        } else {
            for (int j = 0; j <= 2 * M + cow[i].second; ++j) {
                f[j] = max(f[j], f[j - cow[i].second] + cow[i].first);
            }
        }
    }
    int res = 0;
    for (int i = M; i <= 2 * M; ++i) {
        if (f[i] >= 0) res = max(res, f[i] + i - M);
    }
    cout << res << endl;
    return 0;
}