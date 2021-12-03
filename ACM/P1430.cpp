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

constexpr int N = 1010;
int s[N];
int f[N][N];
int l[N][N], r[N][N];

int main() {
    fhj();
    int T, n;
    cin >> T;
    while (T--) {
        memset(f, 0, sizeof f);
        memset(s, 0, sizeof s);
        memset(l, 0x3f, sizeof l);
        memset(r, 0x3f, sizeof r);
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> s[i];
            s[i] += s[i - 1];
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = i; j >= 1; --j) {
                f[j][i] = s[i] - s[j - 1];
                f[j][i] = max(f[j][i], s[i] - s[j - 1] - l[j + 1][i]);
                f[j][i] = max(f[j][i], s[i] - s[j - 1] - r[j][i - 1]);
                if (j == i) l[j][i] = r[j][i] = f[j][i];
                else {
                    l[j][i] = min(f[j][i], l[j + 1][i]);
                    r[j][i] = min(f[j][i], r[j][i - 1]);
                }
            }
        }
        cout << f[1][n] << endl;
    }
    return 0;
}