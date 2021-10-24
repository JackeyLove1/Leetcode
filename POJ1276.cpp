// Author: Jacky
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>
#include <numeric>


using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

inline int count(int x) {
    return __builtin_popcount(x);
}

constexpr int N = 1e6, M = 1e3 + 100, INF = 0x3f3f3f3f;

int f[N];
int s[N], w[N];

typedef pair<int, int> PII;

int main() {
    fhj();
    int n, m;
    while (cin >> m >> n) {
        if (m == 0 || n == 0) {
            cout << 0 << endl;
            continue;
        }
        vector<PII> goods;
        for (int i = 0; i < n; ++i) {
            cin >> s[i] >> w[i];
            for (int k = 1; k <= s[i]; k <<= 1) {
                goods.emplace_back(w[i] * k, w[i] * k);
                s[i] -= k;
            }
            if (s[i]) {
                goods.emplace_back(w[i] * s[i], w[i] * s[i]);
            }
        }
        for (auto &g : goods) {
            for (int j = m; j >= g.first; --j) {
                f[j] = max(f[j], f[j - g.first] + g.second);
            }
        }
        cout << f[m] << endl;
    }
    return 0;
}