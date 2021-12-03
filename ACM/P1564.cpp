#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>
#include <bitset>
#include <queue>
#include <deque>
#include <unordered_set>
#include <cmath>
#include <set>
#include <climits>

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

constexpr int N = 2600;
int w[N], s[N], x;
int f[N];

int main() {
    fhj();
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> x;
        if (x == 1) w[i] = 1;
        else w[i] = -1;
        s[i] = s[i - 1] + w[i];
    }
    memset(f, 0x3f, sizeof f);
    f[0] = 0, f[1] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < i; ++j) {
            if (abs(s[i] - s[j - 1]) <= m ||
                abs(s[i] - s[j - 1]) == i - j + 1) {
                f[i] = min(f[i], f[j - 1] + 1);
                // cout <<"i: " << i << " res:" << f[i] << endl;
            }
        }
    }
    cout << f[n] << endl;
    return 0;
}