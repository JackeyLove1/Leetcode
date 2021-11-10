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
constexpr int N = 1e3 + 100;
bll f[N];

void print(bll x) {
    if (!x) return;
    if (x) print(x / 10);
    putchar(x % 10 + '0');
}

int main() {
    int m, k;
    cin >> m >> k;
    f[0] = 1;
    for (int i = 1; i <= k; ++i) {
        for (int j = i; j <= m; ++j) {
            f[j] += f[j - i];
        }
    }
    print(f[m]);
    return 0;
}